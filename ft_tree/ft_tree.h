/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:20:16 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:22:53 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINT_H
# define FT_PRINT_H
# include "minishell_info.h"
# include <unistd.h>

// tree_utils.c
unsigned char	is_tree_and_or(int token_type);
unsigned char	is_tree_pipe(int token_type);
t_tree			*make_tree_node(int type, t_tree *parent_tree, t_lx_token *data);
void    		tree_traversal(t_tree *cur_tree, int tree_type, \
											void (*handler)(t_tree *));
#endif
