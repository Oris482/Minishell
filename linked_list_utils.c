/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:38:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 17:22:31 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	_is_first_node(t_lx_token *cur_node)
// {
//     return ();
// }
//
// static int	_is_last_node(t_lx_token *cur_node)
// {
//     return ();
// }

t_lx_token  *cut_front_node(t_lx_token *cur_node)
{
	t_lx_token	*const last_node = get_last_node(cur_node);
	t_lx_token	*const new_last_node = cur_node->prev;

	if (cur_node->prev == last_node)
		return (NULL);
	cur_node->prev = last_node;
	cur_node = new_last_node;
	cur_node->next = NULL;
	while (cur_node->prev != last_node)
		cur_node = cur_node->prev;
	cur_node->prev = new_last_node;
	return (cur_node);
}

t_lx_token	*cut_back_node(t_lx_token *cur_node)
{
	t_lx_token	*const last_node = get_last_node(cur_node);
	t_lx_token	*const new_last_node = cur_node;
	t_lx_token	*const rtn_node = cur_node->next;

	if (cur_node == last_node)
		return (NULL);
	rtn_node->prev = last_node;
	cur_node->next = NULL;
	while (cur_node->prev != last_node)
		cur_node = cur_node->prev;
	cur_node->prev = new_last_node;
	return (rtn_node);
}

t_lx_token  *pop_node(t_lx_token **start_node, t_lx_token *end_node)
{
	t_lx_token	*const last_node = get_last_node(*start_node);

	end_node = 
	if (start_node->prev == last_node)
	{
		*cur_node = end_node->next;
		if (*cur_node == NULL)
			return (start_node);
		return (cut_front_node(*cur_node));
	}
	else if (end_node == last_node)
	{
		*cur_node = start_node->prev;
		return (cut_back_node(*cur_node));
	}
	else
	{
		if (*cur_node == start_node || *cur_node == end_node)
			*cur_node = start_node->prev;
		start_node->prev->next = end_node->next;
		end_node->next->prev = start_node->prev;
		start_node->prev = end_node;
		end_node->next = NULL;
	}
	return (start_node);
}

void	merge_linked_list(t_lx_token *dst, t_lx_token *src)
{
	const t_lx_token	*dst_last_node = get_last_node(dst);
	const t_lx_token	*src_last_node = get_last_node(src);

	dst->prev->next = src;
	dst->prev = (t_lx_token *)src_last_node;
	src->prev = (t_lx_token *)dst_last_node;
}
