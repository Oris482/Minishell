/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:26:57 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:30:20 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_H
# define FT_FILE_H

# include "minishell_info.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>

// about_dir.c
DIR				*my_opendir(const char *name);
struct dirent	*my_readdir(DIR *dirp);
int				my_closedir(DIR *dirp);

// dirent_utils.c
t_file			*get_files_cur_pwd(const char *cur_pwd, char dir_flag);

// find_files.c
int				is_matching_file(char *input, t_file *const files);
void			recursive_find_files(t_lx_token **cur, int cur_level, \
											char *pwd, char **splited);
// find_files_utils.c
char			*path_plus_filename(char *pwd, t_file *files, int idx, \
														int dir_flag);
int				get_target_level(char **splited);
#endif