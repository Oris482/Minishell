/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:51:41 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 00:55:24 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_token.h"
#include "ft_tree.h"
#include "ft_check.h"

static void	_handle_subshell(t_tree *head)
{
	t_lx_token	*open_token;
	t_lx_token	*close_token;

	open_token = head->token_data;
	close_token = get_last_token(open_token);
	head->left = make_tree_node(TREE_UNDEFINED, head, head->token_data->next);
	head->token_data = pop_token(&open_token, open_token);
	merge_linked_list(head->token_data, pop_token(&close_token, close_token));
	expand_token_to_tree(head);
}

int	redi_to_left(t_tree *cur_tree, t_lx_token **token_data)
{
	t_lx_token	*prev_node;
	t_lx_token	*end_node;
	t_lx_token	*poped_node;

	if (!is_redi_token(*token_data))
		return (ERROR);
	prev_node = (*token_data)->prev;
	end_node = (*token_data)->next;
	while (end_node->next && end_node->next->token_str == NULL)
		end_node = end_node->next;
	poped_node = pop_token(token_data, end_node);
	if (*token_data == NULL && prev_node != end_node)
		*token_data = prev_node;
	if (cur_tree->left)
		merge_linked_list(cur_tree->left->token_data, poped_node);
	else
		cur_tree->left = make_tree_node(TREE_REDI, cur_tree, poped_node);
	return (SUCCESS);
}

void	remain_to_right(t_tree *cur_tree, t_lx_token *token_data)
{
	const t_lx_token	*remain_last_node = token_data;

	if (!token_data)
		return ;
	while (token_data->prev != remain_last_node)
		token_data = token_data->prev;
	cur_tree->right = make_tree_node(TREE_SIMPLE_CMD, cur_tree, token_data);
	if (token_data->token_type == PARENTHESES_OPEN)
	{
		cur_tree->right->type = TREE_SUBSHELL;
		_handle_subshell(cur_tree->right);
	}
}
