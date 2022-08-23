/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:30:54 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 11:34:11 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

DIR	*my_opendir(const char *name)
{
	DIR	*ret;

	ret = opendir(name);
	if (!ret && printf("%s\n", strerror(errno)))
		exit(1);
	return (ret);
}

struct dirent	*my_readdir(DIR *dirp)
{
	struct dirent	*ret;

	ret = readdir(dirp);
	if (!ret && printf("%s\n", strerror(errno)))
		exit(1);
	return (ret);
}

int	my_closedir(DIR *dirp)
{
	const int	ret = closedir(dirp);

	if (ret == -1 && printf("%s\n", strerror(errno)))
		exit(1);
	return (ret);
}
