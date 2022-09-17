/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:42:44 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 23:49:26 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_ALLOC_H
# define FT_ALLOC_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

// about_alloc.c
void			*my_malloc(size_t size);
void			*my_calloc(size_t count, size_t size);
void			my_free(void *ptr);
void			my_multi_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4);

// free_utils.c
void			*list_tree_free(t_lx_token *list, t_tree *tree);
void			char_dimen2_free(char **strs);
void			files_free(t_file *files);
#endif
