/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:15:48 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 22:19:42 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	count_pipe(t_tree *tree_node, t_pipe *info)
{
	while (tree_node->type != TREE_CMD)
	{
		info->pipe_cnt++;
		tree_node = tree_node->left;
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
