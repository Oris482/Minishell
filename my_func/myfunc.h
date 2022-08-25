/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myfunc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:55:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/25 18:13:50 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYFUNC_H
# define MYFUNC_H
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>

DIR				*my_opendir(const char *name);
struct dirent	*my_readdir(DIR *dirp);
int				my_closedir(DIR *dirp);


#endif
