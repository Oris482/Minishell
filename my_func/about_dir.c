/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:30:54 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/25 18:01:05 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myfunc.h"

DIR	*my_opendir(const char *name)
{
	DIR	*ret;

	ret = opendir(name);
	if (!ret && printf("%s\n", strerror(errno)))
		exit(GENERAL_EXIT_CODE);
	return (ret);
}

struct dirent	*my_readdir(DIR *dirp)
{
	struct dirent	*ret;

	ret = readdir(dirp);
	if (!ret && printf("%s\n", strerror(errno)))
		exit(GENERAL_EXIT_CODE);
	return (ret);
}

int	my_closedir(DIR *dirp)
{
	const int	ret = closedir(dirp);

	if (ret == -1 && printf("%s\n", strerror(errno)))
		exit(GENERAL_EXIT_CODE);
	return (ret);
}
