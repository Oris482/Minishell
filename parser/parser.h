/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/04 20:13:14 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

// typedef struct s_tree
// {
// 	t_lx_token		*data;
// 	struct s_tree	*left;
// 	struct s_tree	*right;
// }	t_tree;

unsigned int	check_syntax_error(t_lx_token *head);
#endif
