/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/25 23:10:23 by minsuki2         ###   ########.fr       */
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
	file.
	dirp = my_opendir(cur_pwd);
	file = my_readdir(dirp);
	while (file && ++i)
	{
		classify(file);
		file = my_readdir(dirp);
	}
	my_closedir(dirp);
	return (i);
}

files[0].name
files[1].name

t_file	*check_cur_dir(const char *cur_pwd)
{
	int				i;
	DIR				*dirp;
	t_file			*files;
	int				n;

	n = count_cur_dir(dirp, cur_pwd);
	printf("n : %d\n", files->file_n);
	files = (t_file *)(my_malloc(sizeof(t_file) * files->file_n));
	dirp = my_opendir(cur_pwd);
	i = -2;
	while (i < files->file_n)
	{
		if (i < 0 && my_readdir(dirp) && ++i)
			continue ;
		files[i].file_set = my_readdir(dirp);
		i++;
	}
	my_closedir(dirp);
	return (files);
}

int main(int ac, char *av[])
{
	t_file	*set;

	printf("%s\n", av[1]);
	set = check_cur_dir(av[1]);

	for (int i = 0; i < set->file_n)
		printf("%s\n", set[i]->);
}
