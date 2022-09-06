/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/06 18:13:52 by jaesjeon         ###   ########.fr       */
=======
/*   Updated: 2022/09/06 20:54:11 by minsuki2         ###   ########.fr       */
>>>>>>> 2c8a4e69a03582ad83cea5c6781c5db70df7d8ac
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

<<<<<<< HEAD
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
=======
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
>>>>>>> 2c8a4e69a03582ad83cea5c6781c5db70df7d8ac

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
