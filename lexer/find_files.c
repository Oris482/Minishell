/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:35:33 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/29 11:40:21 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../minishell.h"
#include "../my_func/myfunc.h"

static int	_check_match_files(char *input, char *name)
{
	while (*input || *name)
	{
		if (*input == '*' && ((*name && (*(input + 1) == '\0' \
			|| *(input + 1) == '/' || *(input + 1) != *name) && name++) \
			|| (*(input + 1) == '/' || *(input + 1) == *name) && input++))
			continue ;
		if (*input == '/' && input++)
			continue ;
		if (*input == *name && input++ && name++)
			continue ;
		return (FALSE);
	}
	return (TRUE);
}

int	is_matching_file(char *input, t_file *const files)
{
	int		i;
	int		cnt;
	char	*wildcard_flag;

	i = 0;
	cnt = 0;
	wildcard_flag = strchr(input, '*');
	while (i < files->n)
	{
		files[i].match_flag = _check_match_files(input, files[i].name);
		if (files[i].match_flag && ++cnt)
			if (!wildcard_flag)
				return (cnt);
		i++;
	}
	return (cnt);
}

// int main(int ac, char *av[])
// {
// 	t_file	*files;

// 	files = get_files_cur_pwd("/Users/minsuki2/Desktop/Minishell/lexer/test_dir", 1);
// 	printf("\n");
// 	printf("\n");
// 	for (int i = 0; i < files->n; i++)
// 	{
// 		if (i == 0)
// 			printf("files_n\t:\t%d\n", files[i].n);
// 		printf("name\t:\t%s\n", files[i].name);
// 		printf("mflag\t:\t%d\n", files[i].match_flag);
// 		printf("type\t:\t%d\n", files[i].type);
// 		printf("\n");
// 	}

// 	is_matching_file("test*/", files);

// 	printf("------------------------------------\n");
// 	for (int i = 0; i < files->n; i++)
// 	{
// 		if (i == 0)
// 			printf("files_n\t:\t%d\n", files[i].n);
// 		printf("name\t:\t%s\n", files[i].name);
// 		printf("mflag\t:\t%d\n", files[i].match_flag);
// 		printf("type\t:\t%d\n", files[i].type);
// 		printf("\n");
// 	}
// 	// system("leaks -q a.out");
// 	return (0);
// }
