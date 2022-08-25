/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:49:35 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/25 19:35:23 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "lexer.h"
#include "../my_func/myfunc.h"

int count_cur_dir(DIR *dirp)
{
	int	i;

	i = 0;
	file = my_readdir(dirp);
	while (file && ++i)
		file = my_readdir(dirp);
	return (i);
}

void	check_cur_dir(char *cur_pwd)
{
	DIR				*dirp;
	struct dirent	*file;
	int				temp;

	print_token_list
		k



	dirp = my_opendir(cur_pwd);
	
	// file = my_readdir(dirp);
	// while (file)
	// {
	//     file = my_readdir(dirp);
	//     clas
	// }
	
	

	return ();
}

int main(int ac, char *av[])
{
	t_file	*set;

	set = mall
	set = check_dirp(av[1]);
}
