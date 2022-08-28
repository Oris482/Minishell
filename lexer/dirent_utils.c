/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/27 21:39:25 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../my_func/myfunc.h"

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

int count_cur_dir(DIR *dirp, const char *cur_pwd)
{
	struct dirent	*file;
	int				i;

	i = 0;
	dirp = my_opendir(cur_pwd);
	file = my_readdir(dirp);
	while (file && ++i)
	{
		classify(file);
		file = my_readdir(dirp);
	}
	my_closedir(dirp);
	return (i - 2);
}

t_file	*check_cur_dir(const char *cur_pwd)
{
	int				i;
	DIR				*dirp;
	t_file			*files;
	int				file_n;

	file_n = count_cur_dir(dirp, cur_pwd);
	files = (t_file *)(my_malloc(sizeof(t_file) * files->n));
	files->n = file_n;
	printf("n : %d\n", files->n);
	dirp = my_opendir(cur_pwd);
	i = -2;
	while (i < files->n)
	{
		if (i < 0 && my_readdir(dirp) && ++i)
			continue ;
		files[i].file_set = my_readdir(dirp);
		files[i].name = files[i].file_set->d_name;
		files[i].match_flag = UNDEFINED;
		files[i].type = files[i].file_set->d_type;
		files[i].pwd = cur_pwd;
		i++;
	}
	my_closedir(dirp);
	return (files);
}

int main(int ac, char *av[])
{
	t_file	*set;

	set = check_cur_dir(av[1]);
	for (int i = 0; i < set->n; i++)
	{
		printf("%d\n", set[i].n);
		printf("%s\n", set[i].name);
		printf("%d\n", set[i].type);
		printf("%s\n", set[i].pwd);
		printf("\n");
	}
}