/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:48:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 17:58:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void _linked_lst_fclean(t_lx_token *cur_list)
{
	while (cur_list)
	{
		my_multi_free(cur_list->token_str, cur_list->interpreted_str, \
															cur_list, NULL);
		cur_list = cur_list->next;
	}
}

static void _tree_node_free(t_tree *cur_tree)
{
	_linked_lst_fclean(cur_tree->token_data);
	my_free(cur_tree);
}

void *list_tree_free(t_lx_token *list, t_tree *tree)
{
	_linked_lst_fclean(list);
	tree_traversal(root_tree, TREE_ALL, _tree_node_free);
	return (NULL);
}
