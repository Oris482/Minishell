/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:38:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/03 17:48:05 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef parser_H
# define parser_H

// typedef struct s_tree
// {
// 	t_lx_token		*data;
// 	struct s_tree	*left;
// 	struct s_tree	*right;
// }	t_tree;

unsigned int	check_syntax_error(t_lx_token *head);
#endif
