/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:31:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/07 22:22:40 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"
#include "myfunc.h"

void	expand_token_to_tree(t_tree *root);

//edit
void    tree_traversal(t_tree *cur_tree, int tree_type, \
								void (*handler)(t_tree *))
{
	if (cur_tree == NULL)
		return ;
	else if (cur_tree->type & tree_type)
		handler(cur_tree);
	tree_traversal(cur_tree->left, tree_type, handler);
	tree_traversal(cur_tree->right, tree_type, handler);
}

// void    tree_traversal(t_tree *cur_tree, int tree_type, \
//                                 void (*handler)(t_tree *))
// {
//     int	pass_right_flag;
//
//     pass_right_flag = FALSE;
//     if (cur_tree == NULL)
//         return ;
//     else if (cur_tree->type & tree_type)
//     {
//         handler(cur_tree);
//         if (tree_type & (TREE_ALL | TREE_OR | TREE_PIPE))
//             pass_right_flag = TRUE;
//     }
//     tree_traversal(cur_tree->left, tree_type, handler);
//     if (!pass_right_flag)
//         tree_traversal(cur_tree->right, tree_type, handler);
//     return ;
// }

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
		if (!subshell_flag && *tree_type != TREE_UNDEFINED \
									&& *tree_type != TREE_CMD)
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
	find_node = find_tree_node(get_last_node(cur->token_data), \
												&cur->type, is_tree_type);
	if (!find_node)
		return ;
	cur->right = make_tree_node(first_type, cur, cut_back_node(find_node));
	cur->left = make_tree_node(first_type, cur, cur->token_data);
	cur->token_data = pop_node(&cur->token_data, find_node, find_node);
	making_tree_node(cur->left, is_tree_type);
}

void	expand_and_or_tree(t_tree *cur)
{
	making_tree_node(cur, is_tree_and_or);
}

void	expand_pipe_tree(t_tree *cur)
{
	making_tree_node(cur, is_tree_pipe);
}

void	handle_subshell(t_tree *head)
{
	t_lx_token	*open_token;
	t_lx_token	*close_token;

	head->left = make_tree_node(TREE_UNDEFINED, head, head->token_data);
	open_token = head->left->token_data;
	head->token_data = pop_node(&head->left->token_data, \
									open_token, open_token);
	close_token = get_last_node(head->left->token_data);
	merge_linked_list(head->token_data, pop_node(&head->left->token_data, \
													close_token, close_token));
	expand_token_to_tree(head);
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
		handle_subshell(cur_tree->right);
	}
}

// void	expand_cmd_tree(t_tree *cur_tree)
// {
//     t_lx_token  *token_data;
//     int					subshell_flag;
//
//     if (cur_tree->type != TREE_CMD)
//         return ;
//     token_data = cur_tree->token_data;
//     parentheses_flag = 0;
//     while (token_data && token_data->next)
//     {
//         subshell_flag += (cur_node->token_type == PARENTHESES_OPEN) \
//                                 - (cur_node->token_type == PARENTHESES_CLOSE);
//         if (subshell_flag)
//         {
//             token_data = token_data->next;
//             continue;
//         }
//         if(!redi_to_left(cur_tree, &token_data))
//             token_data = token_data->next;
//     }
//     remain_to_right(cur_tree, token_data);
//     cur_tree->token_data = NULL;
// }

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

void	expand_token_to_tree(t_tree *root)
{
	tree_traversal(root, TREE_UNDEFINED, expand_and_or_tree);
	tree_traversal(root, TREE_UNDEFINED, expand_pipe_tree);
	tree_traversal(root, TREE_CMD, expand_cmd_tree);
}

int parser(t_tree **root, t_lx_token *head)
{
	*root = make_tree_node(TREE_UNDEFINED, NULL, head);
	expand_token_to_tree(*root);
	print_ascii_tree(*root);
	if (FALSE)
		return (ERROR);
	return (SUCCESS);
}
