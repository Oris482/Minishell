/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:35:33 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/28 20:55:26 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../minishell.h"
#include "../my_func/myfunc.h"

int is_matching_file(char *input, t_file  * const files
		, int dir_flag, int wildcard_flag)
{
	int		i;
	int		cnt;
	int		dir_flag;

	i = 0;
	cnt = 0;
	ft_strch(input, )
	while (i < files->n)
	{
		if (dir_flag && files[i].type != DT_DIR && i++)
			continue ;
		files[i].match_flag = check_match(input, files[i].name);
		if (files[i].match_flag && ++cnt)
			if (!wildcard_flag)
				return (cnt);
		i++;
	}
	return (cnt);
}

int main(int ac, char *av[])
{
	t_file	*files;

	files = check_cur_dir(getenv("PWD"));
	for (int i = 0; i < files->n; i++)
	{
		// printf("%d\n", files[i].n);
		printf("name\t:\t%s\n", files[i].name);
		printf("mflag\t:\t%d\n", files[i].match_flag);
		printf("type\t:\t%d\n", files[i].type);
		// printf("%s\n", files[i].pwd);
		printf("\n");
	}




	is_matching_file("*.c", files, 0, 1);





	printf("------------------------------------\n");
	for (int i = 0; i < files->n; i++)
	{
		// printf("%d\n", files[i].n);
		printf("name\t:\t%s\n", files[i].name);
		printf("mflag\t:\t%d\n", files[i].match_flag);
		printf("type\t:\t%d\n", files[i].type);
		// printf("%s\n", files[i].pwd);
		printf("\n");
	}
	return (0);

}
