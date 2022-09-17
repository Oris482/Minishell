/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:34:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "lexer.h"
#include "parser.h"
#include "myfunc.h"

/*
 * is_xx 함수 계열 프로토타입int 따라감
 */
unsigned char	is_tree_and_or(int token_type)
{
	if (token_type == AND_IF)
		return (TREE_AND);
	else if (token_type == OR_IF)
		return (TREE_OR);
	return (TREE_UNDEFINED);
}

unsigned char	is_tree_pipe(int token_type)
{
	if (token_type == PIPE)
		return (TREE_PIPE);
	return (TREE_CMD);
}

int     is_redi_token(t_lx_token *token)
{
	const int   type = token->token_type;

	if (type == RED_IN || type == RED_OUT || type == HERE_DOC \
														|| type == RED_APD_OUT)
		return (TRUE);
	return (FALSE);
}


t_tree	*make_tree_node(const int type, t_tree *parent_tree, t_lx_token *data)
{
	t_tree	*new_node;

	new_node = (t_tree *)my_calloc(1, sizeof(t_tree));
	new_node->type = type;
	new_node->parent_tree = parent_tree;
	new_node->token_data = data;
	return (new_node);
}

void	tree_traversal(t_tree *cur_tree, int tree_type, \
								void (*handler)(t_tree *))
{
	if (cur_tree == NULL)
		return ;
	tree_traversal(cur_tree->left, tree_type, handler);
	tree_traversal(cur_tree->right, tree_type, handler);
	if (cur_tree->type & tree_type)
		handler(cur_tree);
}
