/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/08 17:57:19 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

void    tree_traversal(t_tree *cur_tree, int tree_type, \
								void (*handler)(t_tree *));
// tree_utils.c
unsigned char	is_tree_and_or(int token_type);
unsigned char	is_tree_pipe(int token_type);
t_tree			*make_tree_node(int type, t_tree *parent_tree, t_lx_token *data);
int     		is_redi_token(t_lx_token *token);

// parser.c
int				parser(t_tree **root, t_lx_token *head);

// print_tree.c
void 			print_ascii_tree(t_tree * t);
// 
#endif
