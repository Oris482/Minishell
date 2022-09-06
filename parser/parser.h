/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/05 15:47:56 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum e_tree_type
{
	TREE_UNDEFINED = 0,
	TREE_AND = 30,
	TREE_OR,
	TREE_PIPE,
	TREE_CMD,
	TREE_REDI,
	TREE_SIMPLE_CMD,
	TREE_SUBSHELL
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

							/* tree_utils.c */
int		is_tree_and_or(int c);
int		is_tree_cmd(int c);
int		is_tree_pipe(int c);
							/* parser.c */


#endif
