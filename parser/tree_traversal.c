/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:19:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/06 21:27:24 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "myfunc.h"

int     is_redi_token(t_lx_token *token)
{
	const int   type = token->token_type;

	if (type == RED_IN || type == RED_OUT || type == HERE_DOC \
														|| type == RED_APD_OUT)
		return (TRUE);
	return (FALSE);
}

t_tree	*make_tree_node(int type, t_tree *parent_tree, t_lx_token *data)
{
	t_tree	*new_node;

	new_node = (t_tree *)my_calloc(1, sizeof(t_tree));
	new_node->type = type;
	new_node->parent_tree = parent_tree;
	new_node->token_data = data;
	return (new_node);
}

int	redi_to_left(t_tree *cur_tree, t_lx_token **token_data)
{
	t_lx_token	*start_node;
	t_lx_token	*end_node;
	t_lx_token	*poped_node;

	if (!is_redi_token(*token_data))
		return (FALSE);
	start_node = *token_data;
	*token_data = (*token_data)->next;
	while ((*token_data)->next && (*token_data)->next->token_str == NULL)
		*token_data = (*token_data)->next;
	end_node = *token_data;
	poped_node = pop_node(token_data, start_node, end_node);
	if (cur_tree->left)
		merge_linked_list(cur_tree->left->token_data, poped_node);
	else
		cur_tree->left = make_tree_node(TREE_REDI, cur_tree, poped_node);
	return (SUCCESS);
}

void	remain_to_right(t_tree *cur_tree, t_lx_token *token_data)
{
	const t_lx_token  *remain_last_node = token_data;

	if (!token_data)
		return ;
	while (token_data->prev != remain_last_node)
		token_data = token_data->prev;
	cur_tree->right = make_tree_node(TREE_SIMPLE_CMD, cur_tree, token_data);
	if (token_data->token_type == PARENTHESES_OPEN)
	{
		cur_tree->right->type = TREE_SUBSHELL;
		//handle_subshell(cur_tree->right);
	}
}

void	expand_cmd_tree(t_tree *cur_tree)
{
	t_lx_token  *token_data;
	int         parentheses_flag;

	if (cur_tree->type != TREE_CMD)
		return ;
	token_data = cur_tree->token_data;
	parentheses_flag = 0;
	while (token_data && token_data->next)
	{
		if (token_data->token_type == PARENTHESES_OPEN)
			parentheses_flag++;
		else if (token_data->token_type == PARENTHESES_CLOSE)
			parentheses_flag--;
		if (parentheses_flag)
		{
			token_data = token_data->next;
			continue;
		}
		if(!redi_to_left(cur_tree, &token_data))
			token_data = token_data->next;
	}
	remain_to_right(cur_tree, token_data);
	cur_tree->token_data = NULL;
}

void    tree_traversal(t_tree *cur_tree, int tree_type, void (*handler)(t_tree *))
{
	int	pass_right_flag;

	pass_right_flag = FALSE;
	if (cur_tree == NULL)
		return ;
	else if (cur_tree->type & tree_type)
	{
		handler(cur_tree);
		if (tree_type & (TREE_ALL | TREE_OR | TREE_PIPE))
			pass_right_flag = TRUE;
	}
	tree_traversal(cur_tree->left, tree_type, handler);
	if (!pass_right_flag)
		tree_traversal(cur_tree->right, tree_type, handler);
	return ;
}

/////////////// debug funtion
t_lx_token	*make_new_token(char *token_str, int token_type, t_lx_token *prev)
{
	t_lx_token *token;

	token = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
	token->token_str = token_str;
	token->token_type = token_type;
	token->prev = prev;
	return (token);
}

int	main(void)
{
	t_tree	*root;
	t_lx_token *token;
	t_lx_token *token_two;
	t_lx_token *token_three;

	root = (t_tree *)my_calloc(1, sizeof(t_tree));
	
	root = make_tree_node(TREE_AND, NULL, make_new_token("&&", AND_IF, NULL));
	
	token = make_new_token("echo", WORD, NULL);
	token->next = make_new_token("<", RED_IN, token);
	token->next->next = make_new_token("input", WORD, token->next);
	token->next->next->next = make_new_token("-n", WORD, token->next->next);
	token->next->next->next->next = make_new_token("abc", WORD, token->next->next->next);
	token->next->next->next->next->next = make_new_token(">>", RED_APD_OUT, token->next->next->next->next);
	token->next->next->next->next->next->next = make_new_token("apd", WORD, token->next->next->next->next->next);
	token->prev = token->next->next->next->next->next->next;
	
	root->left = make_tree_node(TREE_CMD, root, token);
	
	root->right = make_tree_node(TREE_PIPE, root, make_new_token("|", PIPE, NULL));

	token_two = make_new_token("(", PARENTHESES_OPEN, NULL);
	token_two->next = make_new_token("ls", WORD, token_two);
	token_two->next->next = make_new_token(")", PARENTHESES_CLOSE, token_two->next);
	token_two->next->next->next = make_new_token(">", RED_OUT, token_two->next->next);
	token_two->next->next->next->next = make_new_token("output", WORD, token_two->next->next->next);
	token_two->prev = token_two->next->next->next->next;

	root->right->left = make_tree_node(TREE_CMD, root->right, token_two);

	token_three = make_new_token("<<", HERE_DOC, NULL);
	token_three->next = make_new_token("here_doc", WORD, token_three);
	token_three->next->next = make_new_token(NULL, WORD, token_three->next);
	token_three->next->next->interpret_symbol = WILDCARD;
	token_three->next->next->interpreted_str = "ec";
	token_three->next->next->next = make_new_token("echo", WORD, token_three->next->next);
	token_three->prev = token_three->next->next->next;

	root->right->right = make_tree_node(TREE_CMD, root->right, token_three);

	tree_traversal(root, TREE_CMD, expand_cmd_tree);
	print_ascii_tree(root);
	return (0);
}