/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liked_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:44:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/04 20:43:22 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"


// t_lx_token	*cut_front_node()
// {
// }

t_lx_token	*cut_back_node(t_lx_token *cur_node)
{
	t_lx_token *const rtn_node = cur_node->next;
	t_lx_token *const new_last_node = cur_node;

	rtn_node->prev = get_to_last_node(cur_node);
	cur_node->next = NULL;
	while (cur_node->prev->next)
		cur_node = cur_node->prev;
	cur_node->prev = new_last_node;
	return (rtn_node);
}

