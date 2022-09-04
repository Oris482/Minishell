/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:38:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 20:44:49 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lx_token  *cut_front_node(t_lx_token *cur_node)
{
	const t_lx_token    *last_node = get_last_node(cur_node);
	const t_lx_token	*new_last_node = cur_node->prev;

	if (cur_node->prev == last_node)
		return (NULL);
	cur_node->prev = (t_lx_token *)last_node;
	cur_node = (t_lx_token *)new_last_node;
	cur_node->next = NULL;
	while (cur_node->prev != last_node)
		cur_node = cur_node->prev;
	cur_node->prev = (t_lx_token *)new_last_node;
	return (cur_node);
}

// t_lx_token  *cut_back_node(t_lx_token *cur_node)
// {

// }

t_lx_token  *pop_node(t_lx_token **cur_node, \
						t_lx_token *start_node, t_lx_token *end_node)
{
	const t_lx_token    *last_node = get_last_node(*cur_node);
	t_lx_token			*front_node;

	if (start_node->prev == last_node)
		*cur_node = end_node->next;
	else
		start_node->prev->next = end_node->next;
	if (end_node == last_node)
	{
		front_node = **cur_node;
		while (front_node->prev == last_node)
			front_node = front_node->prev;
		front_node->prev = start_node->prev;
	}
	else
		end_node->next->prev = start_node->prev;
	start_node->prev = end_node;
	end_node->next = NULL;
	return (start_node);
}
