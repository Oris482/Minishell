/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:48:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 17:26:48 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_token.h"
#include "ft_tree.h"
#include "ft_string.h"

void	pop_empty_token(t_lx_token *token)
{
	while (token)
	{
		if (token->token_str == NULL && \
			(token->interpreted_str == NULL \
				|| ft_strlen(token->interpreted_str) == 0))
			token = pop_token(&token, token);
		token = token->next;
	}
}

static t_lx_token	*_find_tree_node(t_lx_token *cur_node, \
		unsigned char *tree_type, unsigned char (*is_tree_type)(int))
{
	t_lx_token *const	last = cur_node;
	int					subshell_flag;

	subshell_flag = 0;
	while (cur_node->prev != last)
	{
		subshell_flag += (cur_node->token_type == PARENTHESES_CLOSE) \
								- (cur_node->token_type == PARENTHESES_OPEN);
		*tree_type = is_tree_type(cur_node->token_type);
		if (!subshell_flag && *tree_type != TREE_UNDEFINED \
									&& *tree_type != TREE_CMD)
			return (cur_node);
		cur_node = cur_node->prev;
	}
	*tree_type = is_tree_type(cur_node->token_type);
	return (NULL);
}

void	making_tree_node(t_tree *const cur, unsigned char (*is_tree_type)(int))
{
	t_lx_token	*find_node;
	const int	first_type = is_tree_type(UNDEFINED);

	if (!cur)
		return ;
	find_node = _find_tree_node(get_last_token(cur->token_data), \
												&cur->type, is_tree_type);
	if (!find_node)
		return ;
	cur->right = make_tree_node(first_type, cur, cut_back_token(find_node));
	cur->left = make_tree_node(first_type, cur, cur->token_data);
	cur->token_data = cut_back_token(find_node->prev);
	making_tree_node(cur->left, is_tree_type);
}
