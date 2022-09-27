/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:31:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/27 11:08:01 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_tree.h"
#include "ft_alloc.h"
#include "ft_token.h"

void	expand_and_or_tree(t_tree *cur_tree)
{
	making_tree_node(cur_tree, is_tree_and_or);
}

void	expand_pipe_tree(t_tree *cur_tree)
{
	making_tree_node(cur_tree, is_tree_pipe);
}

void	expand_cmd_tree(t_tree *cur_tree)
{
	t_lx_token	*token_data;
	int			parentheses_flag;

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
			continue ;
		}
		if (redi_to_left(cur_tree, &token_data) == ERROR)
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

t_tree	*parser(t_dict dict[], t_lx_token *head)
{
	t_tree	*root;
	int		exit_code;

	exit_code = check_syntax_error(dict, head);
	if (exit_code != SUCCESS_EXIT_CODE)
	{
		set_exit_status(exit_code);
		return (list_tree_free(head, NULL));
	}
	head->prev = get_last_token(head);
	root = make_tree_node(TREE_UNDEFINED, NULL, head);
	expand_token_to_tree(root);
	return (root);
}
