/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/04 22:54:00 by jaesjeon         ###   ########.fr       */
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

unsigned int	check_syntax_error(t_lx_token *head);
#endif
