/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:40:50 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 02:44:18 by jaesjeon         ###   ########.fr       */
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
		return (0); // exec 부분
}

void	handle_cmd(t_tree *tree_node)
{
	int	backup_fd[2];
	int	exit_code;

	errno = UNDEFINED;
	exit_code = SUCCESS_EXIT_CODE;
	backup_fd[F_READ] = dup(STDIN_FILENO);
	backup_fd[F_WRITE] = dup(STDOUT_FILENO);
	if (backup_fd[F_READ] == ERROR || backup_fd[F_WRITE] == ERROR)
	{
		print_error_str("dup_fd", NULL, NULL, GENERAL_EXIT_CODE);
		exit(GENERAL_EXIT_CODE);
	}
	if (tree_node->left)
		exit_code = redi_middleware(tree_node->left->token_data);
	if (exit_code == SUCCESS_EXIT_CODE && tree_node->right)
		exit_code = simple_cmd_middleware(tree_node->right->token_data);
	set_exit_status(exit_code);
	if (dup2(backup_fd[F_READ], STDIN_FILENO) == ERROR \
		|| dup2(backup_fd[F_WRITE], STDOUT_FILENO) == ERROR)
	{
		print_error_str("dup_fd", NULL, NULL, GENERAL_EXIT_CODE);
		exit (GENERAL_EXIT_CODE);
	}
	close(backup_fd[F_READ]);
	close(backup_fd[F_WRITE]);
}

void	executor(t_tree *root)
{
	tree_traversal(root, TREE_CMD, handle_cmd);
}
