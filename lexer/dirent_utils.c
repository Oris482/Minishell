/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/29 12:02:55 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../my_func/myfunc.h"

void	classify(struct dirent *ent);

int count_cur_dir(DIR *dirp, const char *cur_pwd, int dir_flag)
{
	struct dirent	*file;
	int				i;

	i = 0;
	dirp = my_opendir(cur_pwd);
	file = my_readdir(dirp);
	while (file)
	{
		if (!dir_flag || (dir_flag && file->d_type == DT_DIR))
			i++;
		// classify(file);
		file = my_readdir(dirp);
	}
	my_closedir(dirp);
	return (i - 2);
}

t_file	*get_files_cur_pwd(const char *cur_pwd, int dir_flag)
{
	int				i;
	DIR				*dirp;
	t_file			*files;
	int				files_n;

	files_n = count_cur_dir(dirp, cur_pwd, dir_flag);
	files = (t_file *)(my_malloc(sizeof(t_file) * files_n));
	files->n = files_n;
	dirp = my_opendir(cur_pwd);
	i = -2;
	while (i < files->n)
	{
		if (i < 0 && my_readdir(dirp) && ++i)
			continue ;
		files[i].file_set = my_readdir(dirp);
		if (dir_flag && files[i].file_set->d_type != DT_DIR)
			continue ;
		files[i].name = files[i].file_set->d_name;
		files[i].match_flag = UNDEFINED;
		files[i].type = files[i].file_set->d_type;
		i++;
	}
	my_closedir(dirp);
	return (files);
}

// int main(int ac, char *av[])
// {
//     t_file	*set;
//
//     set = get_files_cur_pwd(av[1], 1);
//     printf("\n");
//     printf("\n");
//     for (int i = 0; i < set->n; i++)
//     {
//         if (i == 0)
//             printf("files_n : %d\n\n", set[i].n);
//         printf("name    : %s\n", set[i].name);
//         printf("type    : %d\n", set[i].type);
//         printf("\n");
//     }
//     system("leaks -q a.out");
//     return (0);
// }

void	classify(struct dirent *ent)
{
	printf("%s\t\t", ent->d_name);
	if (ent->d_type == DT_BLK)
		printf("Block Device\n");
	else if (ent->d_type == DT_CHR)
		printf("Character Device\n");
	else if (ent->d_type == DT_DIR)
		printf("Directory\n");
	else if (ent->d_type == DT_LNK)
		printf("Symbolic Link\n");
	else if (ent->d_type == DT_REG)
		printf("Regular File\n");
	else if (ent->d_type == DT_SOCK)
		printf("Unix Domain Socket\n");
	else
		printf("Unknown Type File\n");
}
