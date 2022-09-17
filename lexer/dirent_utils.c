/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 13:30:59 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cur_dir(const char *cur_pwd, char dir_flag)
{
	struct dirent	*file;
	DIR				*dirp;
	int				i;

	i = 0;
	dirp = my_opendir(cur_pwd);
	file = my_readdir(dirp);
	while (file)
	{
		if (!dir_flag || (dir_flag && file->d_type == DT_DIR))
			i++;
		file = my_readdir(dirp);
	}
	my_closedir(dirp);
	return (i);
}

t_file	*get_files_cur_pwd(const char *cur_pwd, char dir_flag)
{
	int				i;
	struct dirent	*file_set;
	t_file			*files;
	int				files_n;

	files_n = count_cur_dir(cur_pwd, dir_flag);
	if (!files_n)
		return (NULL);
	files = (t_file *)(my_calloc(files_n, sizeof(t_file)));
	files->n = files_n;
	files->dirp = my_opendir(cur_pwd);
	i = 0;
	while (i < files->n)
	{
		file_set = my_readdir(files->dirp);
		if (dir_flag && file_set->d_type != DT_DIR)
			continue ;
		// files[i].name = ft_strdup(file_set->d_name);
		files[i].name = file_set->d_name;
		// files[i].match_flag = UNDEFINED;
		files[i].type = file_set->d_type;
		i++;
	}
	// my_closedir(files->dirp);
	return (files);
}
