/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:38:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 22:30:45 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_is_first_node(t_lx_token *cur_node)
{
	return (cur_node->prev == get_last_node(cur_node));
}

static int	_is_last_node(t_lx_token *cur_node)
{
	return (cur_node == get_last_node(cur_node));
}

t_lx_token  *cut_front_node(t_lx_token *cur_node)
{
	const t_lx_token    *last_node = get_last_node(cur_node);
	const t_lx_token	*new_last_node = cur_node->prev;

	if (_is_first_node(cur_node))
		return (NULL);
	cur_node->prev = (t_lx_token *)last_node;
	cur_node = (t_lx_token *)new_last_node;
	cur_node->next = NULL;
	while (cur_node->prev != last_node)
		cur_node = cur_node->prev;
	cur_node->prev = (t_lx_token *)new_last_node;
	return (cur_node);
}

t_lx_token	*cut_back_node(t_lx_token *cur_node)
{
	t_lx_token *const rtn_node = cur_node->next;
	t_lx_token *const new_last_node = cur_node;

	if (_is_last_node(cur_node))
		return (NULL);
	rtn_node->prev = get_last_node(cur_node);
	cur_node->next = NULL;
	while (cur_node->prev->next)
		cur_node = cur_node->prev;
	cur_node->prev = new_last_node;
	return (rtn_node);
}

t_lx_token  *pop_node(t_lx_token **cur_node, \
						t_lx_token *start_node, t_lx_token *end_node)
{
	if (_is_first_node(start_node))
	{
		*cur_node = end_node->next;
		return (cut_front_node(*cur_node));
	}
	else if (_is_last_node(end_node))
	{
		*cur_node = start_node->prev;
		return (cut_back_node(*cur_node));
	}
	else
	{
		if (*cur_node == start_node)
			*cur_node = start_node->prev;
		start_node->prev->next = end_node->next;
		end_node->next->prev = start_node->prev;
		start_node->prev = end_node;
		end_node->next = NULL;
	}
	return (start_node);
}
