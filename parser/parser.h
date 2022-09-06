/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/06 18:13:52 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum e_tree_type
{
	TREE_UNDEFINED = 1,
	TREE_AND = 2,
	TREE_OR = 4,
	TREE_PIPE = 8,
	TREE_CMD = 16,
	TREE_REDI = 32,
	TREE_SIMPLE_CMD = 64,
	TREE_SUBSHELL = 128,
	TREE_ALL = 256
};

typedef struct s_tree
{
	int				type;
	t_lx_token		*token_data;
	struct s_tree	*parent_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

int				parser(t_lx_token *head);
unsigned int	check_syntax_error(t_lx_token *head);

// tree_utils.c
int		is_tree_and_or(int c);
int		is_tree_cmd(int c);
int		is_tree_pipe(int c);
// parser.c

// print_tree.c
void print_ascii_tree(t_tree * t);


#endif
