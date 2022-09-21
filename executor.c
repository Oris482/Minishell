/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:40:50 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 22:17:32 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_string.h"
#include "ft_token.h"

int	run_simple_cmd(t_lx_token *token)
{
	t_lx_token	*backup;
	int			builtin_idx;
	int			status;
	pid_t		pid;

	// 함수 분리 예정
	while (token)
	{
		if (token->interpret_symbol)
		{
			backup = token->next;
			token  = interpreter(token);
			token->next = backup;
		}
		token = token->next;
	}
	//
	builtin_idx = is_builtin(get_token_str(token));
	if (builtin_idx)
		return (builtin_middleware(token, builtin_idx));
	else
	{
		pid = my_fork();
		set_int_quit_signal(SIG_DFL, SIG_DFL);
		if (pid == CHILD_PID)
			execute_middleware(token);
		set_int_quit_signal(SIG_IGN, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(1, "Int : 2\n", 9);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			write(1, "Quit : 3\n", 10);
		set_init_signal();
		return (get_exit_code(status));
	}
	return (GENERAL_EXIT_CODE);
}

int	handle_fd(int *backup_fd, int task)
{
	if (task == BACKUP)
	{
		backup_fd[F_READ] = my_dup(STDIN_FILENO);
		backup_fd[F_WRITE] = my_dup(STDOUT_FILENO);
	}
	else if (task == RESTORE)
	{
		my_dup2(backup_fd[F_READ], STDIN_FILENO);
		my_dup2(backup_fd[F_WRITE], STDOUT_FILENO);
		close(backup_fd[F_READ]);
		close(backup_fd[F_WRITE]);
	}
	else
		return (FALSE);
	return (SUCCESS);
}

int	run_subshell(t_tree *tree_node, char set_exit_status_flag)
{
	pid_t	pid;
	int		status;

	pid = my_fork();
	if (pid == CHILD_PID)
		exit(executor(tree_node->left, set_exit_status_flag));
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
			exit_code = run_simple_cmd(tree_node->right->token_data);
		else
			exit_code = run_subshell(tree_node->right, set_exit_status_flag);
	}
	if (set_exit_status_flag)
		set_exit_status(exit_code);
	if (handle_fd(backup_fd, RESTORE) == FALSE)
		return (GENERAL_EXIT_CODE);
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
