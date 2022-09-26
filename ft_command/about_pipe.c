/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:35:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/27 00:40:20 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"
#include "ft_alloc.h"

static void	_set_pipe_for_child(t_pipe *info)
{
	const int	idx = info->fork_cnt;

	if (idx != 0)
	{
		my_dup2(info->fd[!(idx % 2)][F_READ], STDIN_FILENO);
		close(info->fd[!(idx % 2)][F_READ]);
	}
	if (idx != info->pipe_cnt)
	{
		my_dup2(info->fd[idx % 2][F_WRITE], STDOUT_FILENO);
		close(info->fd[idx % 2][F_WRITE]);
	}
	if (idx == 0)
		close(info->fd[A][F_READ]);
	else if (idx == info->pipe_cnt)
		close(!(idx % 2) * info->fd[A][F_WRITE] \
					+ (idx % 2) * info->fd[B][F_WRITE]);
	else
		close((idx % 2) * info->fd[A][F_READ] \
					+ !(idx % 2) * info->fd[B][F_READ]);
}

static void	_pipe_child(t_dict dict[], t_tree *tree_node, \
							char set_exit_status_flag, t_pipe *info)
{
	int	exit_code;

	_set_pipe_for_child(info);
	exit_code = handle_cmd(dict, tree_node, set_exit_status_flag);
	exit(exit_code);
}

static void	_handle_pipe_fd(t_pipe *info)
{
	const int	idx = info->fork_cnt;

	if (idx == 0)
		close(info->fd[A][F_WRITE]);
	else if (idx != info->pipe_cnt)
	{
		close((idx % 2) * info->fd[B][F_WRITE] \
					+ !(idx % 2) * info->fd[A][F_WRITE]);
		close((idx % 2) * info->fd[A][F_READ] \
					+ !(idx % 2) * info->fd[B][F_READ]);
	}
	else
	{
		close((idx % 2) * info->fd[A][F_READ] \
					+ !(idx % 2) * info->fd[B][F_READ]);
		close((idx % 2) * info->fd[B][F_WRITE] \
					+ !(idx % 2) * info->fd[A][F_WRITE]);
		close((idx % 2) * info->fd[B][F_READ] \
					+ !(idx % 2) * info->fd[A][F_READ]);
	}
}

static void	_handle_pipe(t_dict dict[], t_tree *tree_node, \
							char set_exit_status_flag, t_pipe_info *pipe_info)
{
	pid_t	pid;

	if (tree_node->type != TREE_CMD)
		_handle_pipe(dict, tree_node->left, FALSE, pipe_info);
	else
	{
		my_pipe(pipe_info->pipe.fd[pipe_info->pipe.fork_cnt % 2]);
		pid = my_fork();
		if (pid == CHILD_PID)
			_pipe_child(dict, tree_node, set_exit_status_flag, \
															&pipe_info->pipe);
		add_pid_to_list(pipe_info->pid_list, pid);
		_handle_pipe_fd(&pipe_info->pipe);
		pipe_info->pipe.fork_cnt++;
		return ;
	}
	_handle_pipe(dict, tree_node->right, set_exit_status_flag, pipe_info);
}

int	init_pipe(t_dict dict[], t_tree *tree_node, char set_exit_status_flag)
{
	t_pipe_info	pipe_info;
	t_pid_list	*tmp;
	int			status;

	pipe_info.pipe.pipe_cnt = 0;
	pipe_info.pipe.fork_cnt = 0;
	pipe_info.pid_list = (t_pid_list *)my_calloc(1, sizeof(t_pid_list));
	count_pipe(tree_node, &pipe_info.pipe);
	_handle_pipe(dict, tree_node, set_exit_status_flag, &pipe_info);
	set_int_quit_signal(SIG_IGN, SIG_IGN);
	while (pipe_info.pid_list)
	{
		waitpid(pipe_info.pid_list->pid, &status, WUNTRACED);
		tmp = pipe_info.pid_list;
		pipe_info.pid_list = pipe_info.pid_list->next;
		my_free(tmp);
	}
	set_init_signal();
	if (set_exit_status_flag)
		set_exit_status(get_exit_code(status));
	return (SUCCESS_EXIT_CODE);
}
