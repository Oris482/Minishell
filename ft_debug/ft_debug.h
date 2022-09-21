/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:20:36 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 17:00:56 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H
# define FT_DEBUG_H

# include <string.h>
# include <stdio.h>

// debug_print_evnp.c
int		print_dictionary_lst(void);
int		print_strs(char *strs[]);

// debug_print_tree.c
void	print_ascii_tree(t_tree *t);

// debug_function.c
void	print_token_list(t_lx_token *token_list);
void	classify(struct dirent *ent);
void	print_token_next(t_lx_token *token_list);
void	print_token_prev(t_lx_token *token_list);
#endif