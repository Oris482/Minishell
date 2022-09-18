/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:35:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 01:09:44 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"

static void	_set_pipe_for_child(t_pipe *info)
{
	const int	idx = info->fork_cnt;

	if (idx != 0)
		if (dup2(info->fd[!(idx % 2)][F_READ], STDIN_FILENO) == ERROR)
			exit(GENERAL_EXIT_CODE);
	if (idx != info->pipe_cnt)
		if (dup2(info->fd[idx % 2][F_WRITE], STDOUT_FILENO) == ERROR)
			exit(GENERAL_EXIT_CODE);
	close(info->fd[EVEN][F_READ]);
	close(info->fd[EVEN][F_WRITE]);
	close(info->fd[ODD][F_READ]);
	close(info->fd[ODD][F_WRITE]);
}

static void	_pipe_child(t_tree *tree_node, \
							char set_exit_status_flag, t_pipe *info)
{
	int	exit_code;

	_set_pipe_for_child(info);
	exit_code = handle_cmd(tree_node, set_exit_status_flag);
	exit(exit_code);
}

static void	_handle_pipe_fd(t_pipe *info)
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

static void	_handle_pipe(t_tree *tree_node, \
								char set_exit_status_flag, t_pipe *info)
{
	pid_t	pid;
	int		status;

	if (tree_node->type == TREE_PIPE)
		info->pipe_cnt++;
	if (tree_node->type != TREE_CMD)
		_handle_pipe(tree_node->left, FALSE, info);
	else
	{
		if (pipe(info->fd[info->fork_cnt % 2]) == ERROR)
			exit(GENERAL_EXIT_CODE);
		pid = fork();
		if (pid == ERROR)
			exit(GENERAL_EXIT_CODE);
		else if (pid == 0)
			_pipe_child(tree_node, set_exit_status_flag, info);
		_handle_pipe_fd(info);
		info->fork_cnt++;
		waitpid(pid, &status, WUNTRACED);
		if (set_exit_status_flag)
			set_exit_status(get_exit_code(status));
		return ;
	}
	_handle_pipe(tree_node->right, set_exit_status_flag, info);
}

int	init_pipe(t_tree *tree_node, char set_exit_status_flag)
{
	t_pipe	info;

	info.pipe_cnt = 0;
	info.fork_cnt = 0;
	_handle_pipe(tree_node, set_exit_status_flag, &info);
	close (info.fd[EVEN][F_READ]);
	close (info.fd[EVEN][F_WRITE]);
	close (info.fd[ODD][F_READ]);
	close (info.fd[ODD][F_WRITE]);
	return (SUCCESS_EXIT_CODE);
}
