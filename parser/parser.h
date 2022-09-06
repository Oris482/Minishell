/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/06 20:54:11 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

# define TREE_UNDEFINED			0B00000001
# define TREE_AND				0B00000010
# define TREE_OR				0B00000100
# define TREE_PIPE				0B00001000
# define TREE_CMD				0B00010000
# define TREE_REDI				0B00100000
# define TREE_SIMPLE_CMD		0B01000000
# define TREE_SUBSHELL			0B10000000

// enum e_tree_type
// {
//     TREE_UNDEFINED = 0,
//     TREE_AND = 30,
//     TREE_OR,
//     TREE_PIPE,
//     TREE_CMD,
//     TREE_REDI,
//     TREE_SIMPLE_CMD,
//     TREE_SUBSHELL
// };

typedef struct s_tree
{
	unsigned char	type;
	t_lx_token		*token_data;
	struct s_tree	*parent_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

int				parser(t_lx_token *head);
unsigned int	check_syntax_error(t_lx_token *head);

// tree_utils.c
unsigned char	is_tree_and_or(int token_type);
unsigned char	is_tree_pipe(int token_type);

// parser.c

// print_tree.c
void print_ascii_tree(t_tree * t);


#endif
