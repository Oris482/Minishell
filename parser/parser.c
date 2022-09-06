/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:31:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/06 22:12:27 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
// #include "lexer.h"
// #include "minishell.h"

#include "./parser.h"
#include "../lexer/lexer.h"
#include "../minishell.h"

t_lx_token *find_tree_node(t_lx_token *cur_node, \
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
		if (!subshell_flag && *tree_type != TREE_UNDEFINED && *tree_type != TREE_CMD)
			return (cur_node);
		cur_node = cur_node->prev;
	}
	*tree_type = is_tree_type(cur_node->token_type);
	return (NULL);
}

void making_tree_node(t_tree *const cur, unsigned char(* is_tree_type)(int))
{
	t_lx_token	*find_node;
	const int	first_type = is_tree_type(UNDEFINED);

	if (!cur)
		return ;
	find_node = find_tree_node(get_last_node(cur->token_data), &cur->type, is_tree_type);
	if (!find_node)
		return ;
	cur->right = make_tree_node(first_type, cur, cut_back_node(find_node));
	cur->left = make_tree_node(first_type, cur, cur->token_data);
	cur->token_data = pop_node(&cur->token_data, find_node, find_node);
	making_tree_node(cur->left, is_tree_type);
}

void	handler_and_or(t_tree *cur)
{
	making_tree_node(cur, is_tree_and_or);
}

void	handler_pipe(t_tree *cur)
{
	making_tree_node(cur, is_tree_pipe);
}

/* 탐색만 하는 함수
 * 원하는 type이 나오면 handler으로 작동을 수행함.
 * 수행한 곳에서는 따로 left right를 들어가지 않음
 */
void recur_search_handle_tree(t_tree *cur, int tree_type, void (*handler)(t_tree *))
{
	if (cur->type & tree_type)
		handler(cur);
	else
	{
		recur_search_handle_tree(cur->left, tree_type, handler);
		recur_search_handle_tree(cur->right, tree_type, handler);
	}
}

int parser(t_lx_token *head)
{
	t_tree		*root;

	root = (t_tree *)make_new_node(sizeof(t_tree));
	root->type = TREE_UNDEFINED;
	root->token_data = head;
	recur_search_handle_tree(root, TREE_UNDEFINED, handler_and_or);
	recur_search_handle_tree(root, TREE_UNDEFINED, handler_pipe);
	print_ascii_tree(root);
	return (SUCCESS);
}
