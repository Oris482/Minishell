/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/31 17:55:37 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../my_func/myfunc.h"

void	classify(struct dirent *ent);

int	count_cur_dir(const char *cur_pwd, int dir_flag)
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
	return (i - 2);
}

t_file	*get_files_cur_pwd(const char *cur_pwd, int dir_flag)
{
	int				i;
	struct dirent	*file_set;
	t_file			*files;
	int				files_n;

	files_n = count_cur_dir(cur_pwd, dir_flag);
	if (!files_n)
		return (NULL);
	files = (t_file *)(my_malloc(sizeof(t_file) * files_n));
	files->n = files_n;
	files->dirp = my_opendir(cur_pwd);
	i = -2;
	while (i < files->n)
	{
		if (i < 0 && my_readdir(files->dirp) && ++i + 2)
			continue ;
		file_set = my_readdir(files->dirp);
		if (dir_flag && file_set->d_type != DT_DIR)
			continue ;
		files[i].name = file_set->d_name;
		files[i].match_flag = UNDEFINED;
		files[i].type = file_set->d_type;
		i++;
	}
	return (files);
}

int main()
{
	t_file	*set;


	set = get_files_cur_pwd("", 0);
	for (int i = 0; i < set->n; i++)
	{
		if (i == 0)
			printf("files_n : %d\n\n", set[i].n);
		printf("name    : %s\n", set[i].name);
		printf("type    : %d\n", set[i].type);
		printf("\n");
	}
	my_closedir(set->dirp);
	free(set);
	return (0);
}
