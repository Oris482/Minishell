/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:35:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 20:46:48 by jaesjeon         ###   ########.fr       */
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
		my_dup2(info->fd[!(idx % 2)][F_READ], STDIN_FILENO);
	if (idx != info->pipe_cnt)
		my_dup2(info->fd[idx % 2][F_WRITE], STDOUT_FILENO);
	if (idx == 0)
		close(info->fd[A][F_READ]);
	else if (idx == info->pipe_cnt)
		close(!(idx % 2) * info->fd[A][F_WRITE] \
					+ (idx % 2) * info->fd[B][F_WRITE]);
	else
		close((idx % 2) * info->fd[A][F_READ] \
					+ !(idx % 2) * info->fd[B][F_READ]);
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

void	add_pid_to_list(t_pid_list *pid_list, pid_t pid)
{
	if (pid_list->pid == 0)
		pid_list->pid = pid;
	else
	{
		while (pid_list->next)
			pid_list = pid_list->next;
		pid_list->next = (t_pid_list *)my_calloc(1, sizeof(t_pid_list));
		pid_list->next->pid = pid;
	}
}

static void	_handle_pipe(t_tree *tree_node, char set_exit_status_flag, \
							t_pipe *info, t_pid_list *pid_list)
{
	pid_t	pid;

	if (tree_node->type != TREE_CMD)
		_handle_pipe(tree_node->left, FALSE, info, pid_list);
	else
	{
		my_pipe(info->fd[info->fork_cnt % 2]);
		pid = my_fork();
		if (pid == CHILD_PID)
			_pipe_child(tree_node, set_exit_status_flag, info);
		add_pid_to_list(pid_list, pid);
		_handle_pipe_fd(info);
		info->fork_cnt++;
		return ;
	}
	_handle_pipe(tree_node->right, set_exit_status_flag, info, pid_list);
}

void	count_pipe(t_tree *tree_node, t_pipe *info)
{
	while (tree_node->type != TREE_CMD)
	{
		info->pipe_cnt++;
		tree_node = tree_node->left;
	}
}

int	init_pipe(t_tree *tree_node, char set_exit_status_flag)
{
	t_pipe		info;
	t_pid_list	*pid_list;
	t_pid_list	*tmp;
	int			status;

	info.pipe_cnt = 0;
	info.fork_cnt = 0;
	pid_list = (t_pid_list *)my_calloc(1, sizeof(t_pid_list));
	count_pipe(tree_node, &info);
	_handle_pipe(tree_node, set_exit_status_flag, &info, pid_list);
	while (pid_list)
	{
		waitpid(pid_list->pid, &status, WUNTRACED);
		tmp = pid_list;
		pid_list = pid_list->next;
		my_free(tmp);
	}
	if (set_exit_status_flag)
		set_exit_status(get_exit_code(status));
	return (SUCCESS_EXIT_CODE);
}
