/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:30:54 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 21:12:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
