/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myfunc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:55:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/01 13:25:49 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYFUNC_H
# define MYFUNC_H
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>

DIR				*my_opendir(const char *name);
struct dirent	*my_readdir(DIR *dirp);
int				my_closedir(DIR *dirp);
void			*my_malloc(size_t size);
void			*my_calloc(size_t count, size_t size);
void			my_free(void *ptr);
void			my_multi_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4);

#endif
