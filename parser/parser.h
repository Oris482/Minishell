/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/07 23:45:36 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum e_tree_type
{
	TREE_UNDEFINED =	0b00000001,
	TREE_AND = 			0b00000010,
	TREE_OR =			0b00000100,
	TREE_PIPE =			0b00001000,
	TREE_CMD =			0b00010000,
	TREE_REDI =			0b00100000,
	TREE_SIMPLE_CMD =	0b01000000,
	TREE_SUBSHELL =		0b10000000,
	TREE_ALL = 			0b11111111
};

typedef struct s_tree
{
	unsigned char	type;
	t_lx_token		*token_data;
	struct s_tree	*parent_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


// tree_utils.c
unsigned char	is_tree_and_or(int token_type);
unsigned char	is_tree_pipe(int token_type);
t_tree			*make_tree_node(int type, t_tree *parent_tree, t_lx_token *data);
int     		is_redi_token(t_lx_token *token);

// parser.c
int				parser(t_tree **root, t_lx_token *head);

// print_tree.c
void print_ascii_tree(t_tree * t);
#endif
