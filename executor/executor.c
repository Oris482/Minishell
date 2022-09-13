/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:40:50 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/13 14:30:52 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp_ignore_capital("echo", str) == SUCCESS)
		return (BI_ECHO);
	else if (ft_strcmp_ignore_capital("cd", str) == SUCCESS)
		return (BI_CD);
	else if (ft_strcmp_ignore_capital("pwd", str) == SUCCESS)
		return (BI_PWD);
	else if (ft_strcmp_ignore_capital("export", str) == SUCCESS)
		return (BI_EXPORT);
	else if (ft_strcmp_ignore_capital("unset", str) == SUCCESS)
		return (BI_UNSET);
	else if (ft_strcmp_ignore_capital("env", str) == SUCCESS)
		return (BI_ENV);
	else if (ft_strcmp_ignore_capital("exit", str) == SUCCESS)
		return (BI_EXIT);
	else
		return (FALSE);
}

int	builtin_middleware(t_lx_token *token, int builtin_idx)
{
	if (builtin_idx == BI_ECHO)
		return (builtin_echo(token));
	else if (builtin_idx == BI_CD)
		return (builtin_cd(token));
	else if (builtin_idx == BI_PWD)
		return (builtin_pwd());
	// else if (builtin_idx == BI_EXPORT)
	// 	return (builtin_export(token));
	// else if (builtin_idx == BI_UNSET)
	// 	return (builtin_unset(token));
	// else if (builtin_idx == BI_ENV)
	// 	return (builtin_env(token));
	else if (builtin_idx == BI_EXIT)
		return (builtin_exit(token));
	else
		return (ERROR);
}

int	simple_cmd_middleware(t_lx_token *token)
{
	int	builtin_idx;

	builtin_idx = is_builtin(get_token_str(token));
	if (builtin_idx)
		return (builtin_middleware(token, builtin_idx));
	else
		return (GENERAL_EXIT_CODE); // exec 부분
}

int	handle_fd(int *backup_fd, int task)
{
	if (task == BACKUP)
	{
		backup_fd[F_READ] = dup(STDIN_FILENO);
		backup_fd[F_WRITE] = dup(STDOUT_FILENO);
		if (backup_fd[F_READ] == ERROR || backup_fd[F_WRITE] == ERROR)
			return (FALSE);
	}
	else if (task == RESTORE)
	{
		if (dup2(backup_fd[F_READ], STDIN_FILENO) == ERROR \
			|| dup2(backup_fd[F_WRITE], STDOUT_FILENO) == ERROR)
			return (FALSE);
		close(backup_fd[F_READ]);
		close(backup_fd[F_WRITE]);
	}
	else
		return (FALSE);
	return (SUCCESS);
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFSTOPPED(status))
		return (17 + 128);
	else if (WIFCONTINUED(status))
		return (19 + 128);
	else
		return (GENERAL_EXIT_CODE);
}

int	run_subshell(t_tree *tree_node, char set_exit_status_flag)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		return (executor(tree_node->left, set_exit_status_flag));
	waitpid(pid, &status, WUNTRACED);
	return (get_exit_code(status));
}

int	handle_cmd(t_tree *tree_node, char set_exit_status_flag)
{
	int	backup_fd[2];
	int	exit_code;

	errno = UNDEFINED;
	exit_code = SUCCESS_EXIT_CODE;
	if (handle_fd(backup_fd, BACKUP) == FALSE)
		return (GENERAL_EXIT_CODE);
	if (tree_node->left)
		exit_code = redi_middleware(tree_node->left->token_data);
	if (exit_code == SUCCESS_EXIT_CODE && tree_node->right)
	{
		if (tree_node->right->type == TREE_SIMPLE_CMD)
			exit_code = simple_cmd_middleware(tree_node->right->token_data);
		else
			exit_code = run_subshell(tree_node->right, set_exit_status_flag);
	}
	if (set_exit_status_flag)
		set_exit_status(exit_code);
	if (handle_fd(backup_fd, RESTORE) == FALSE)
		return (GENERAL_EXIT_CODE);
	return (exit_code);
}

void	set_pipe_for_child(t_pipe *info)
{
	const int	idx = info->fork_cnt;

	if (idx != 0)
	{
		printf("-------------------\nIN = %d\n", info->fd[!(idx % 2)][F_READ]);
		if (dup2(info->fd[!(idx % 2)][F_READ], STDIN_FILENO) == ERROR)
			exit(GENERAL_EXIT_CODE);
	}
	else
		printf("-------------------\nIN = %d\n", STDIN_FILENO);
	if (idx != info->pipe_cnt)
	{
		printf("OUT = %d\n-------------------\n", info->fd[idx % 2][F_WRITE]);
		if (dup2(info->fd[idx % 2][F_WRITE], STDOUT_FILENO) == ERROR)
			exit(GENERAL_EXIT_CODE);
	}
	else
		printf("OUT = %d\n-------------------\n", STDOUT_FILENO);
	close(info->fd[EVEN][F_READ]);
	close(info->fd[EVEN][F_WRITE]);
	close(info->fd[ODD][F_READ]);
	close(info->fd[ODD][F_WRITE]);
}

void	pipe_child(t_tree *tree_node, char set_exit_status_flag, t_pipe *info)
{
	int	exit_code;

	set_pipe_for_child(info);
	exit_code = handle_cmd(tree_node, set_exit_status_flag);
	if (exit_code != SUCCESS_EXIT_CODE)
	{
		printf("pipe_child\n");
	}
	exit(exit_code);
}

void	handle_pipe_fd(t_pipe *info)
{
	const int	idx = info->fork_cnt;

	if (idx == 0)
		close(info->fd[EVEN][F_WRITE]);
	else if (idx == info->pipe_cnt)
	{
		if (idx % 2)
			close(info->fd[ODD][F_WRITE]);
		else
			close(info->fd[EVEN][F_WRITE]);
	}
	else
	{
		if (idx % 2)
		{
			close(info->fd[ODD][F_WRITE]);
			close(info->fd[EVEN][F_READ]);
		}
		else
		{
			close(info->fd[EVEN][F_WRITE]);
			close(info->fd[ODD][F_READ]);
		}
	}
}

int	handle_pipe(t_tree *tree_node, char set_exit_status_flag, t_pipe *info)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	if (tree_node->type == TREE_PIPE)
		info->pipe_cnt++;
	if (tree_node->type != TREE_CMD)
		handle_pipe(tree_node->left, FALSE, info);
	else
	{
		if (pipe(info->fd[info->fork_cnt % 2]) == ERROR)
			exit(GENERAL_EXIT_CODE);
		pid = fork();
		if (pid == ERROR)
			exit(GENERAL_EXIT_CODE);
		else if (pid == 0)
			pipe_child(tree_node, set_exit_status_flag, info);
		handle_pipe_fd(info);
		info->fork_cnt++;
		waitpid(pid, &status, WUNTRACED);
		return (get_exit_code(status));
	}
	exit_code = handle_pipe(tree_node->right, set_exit_status_flag, info);
	return (exit_code);
}

int	init_pipe(t_tree *tree_node, char set_exit_status_flag)
{
	t_pipe	info;
	int		exit_code;

	info.pipe_cnt = 0;
	info.fork_cnt = 0;
	exit_code = handle_pipe(tree_node, set_exit_status_flag, &info);
	if (set_exit_status_flag)
		set_exit_status(exit_code);
	close (info.fd[EVEN][F_READ]);
	close (info.fd[EVEN][F_WRITE]);
	close (info.fd[ODD][F_READ]);
	close (info.fd[ODD][F_WRITE]);
	return (exit_code);
}

int	executor(t_tree *root, char set_exit_status_flag)
{
	int	exit_code;

	if (root->type == TREE_AND || root->type == TREE_OR)
	{
		exit_code = executor(root->left, set_exit_status_flag);
		if (root->type == TREE_AND && exit_code == SUCCESS_EXIT_CODE)
			exit_code = executor(root->right, set_exit_status_flag);
		else if (root->type == TREE_OR && exit_code != SUCCESS_EXIT_CODE)
			exit_code = executor(root->right, set_exit_status_flag);
	}
	if (root->type == TREE_PIPE)
		return (init_pipe(root, set_exit_status_flag));
	if (root->type == TREE_CMD)
		return (handle_cmd(root, set_exit_status_flag));
	return (exit_code);
}
