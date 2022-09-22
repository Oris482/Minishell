/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:42:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 17:12:32 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	initialize(int fd, char **disk)
{
	if (disk[fd] == 0)
	{
		disk[fd] = ft_strdup("");
		if (disk[fd] == NULL)
			return (0);
		return (1);
	}
	else
		return (1);
}

char	*make_line(int fd, char **disk, ssize_t len)
{
	char	*ret;
	char	*tmp;
	int		nl_idx;

	if (disk[fd] == NULL || len == -1)
		return (NULL);
	nl_idx = ft_isinnl(fd, disk);
	if (nl_idx != -1)
	{
		ret = ft_substr(disk[fd], 0, nl_idx + 1);
		tmp = ft_substr(disk[fd], nl_idx + 1, ft_strlen(disk[fd]));
		free(disk[fd]);
		disk[fd] = tmp;
		if (*disk[fd] != '\0')
			return (ret);
	}
	else
		ret = ft_strdup(disk[fd]);
	free(disk[fd]);
	disk[fd] = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*disk[OPEN_MAX];
	char		*buffer;
	char		*joined;
	ssize_t		len;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	len = read(fd, buffer, BUFFER_SIZE);
	while (len > 0)
	{
		buffer[len] = '\0';
		if (!initialize(fd, disk))
			return (NULL);
		joined = ft_strjoin(disk[fd], buffer);
		free(disk[fd]);
		if (joined == NULL)
			return (NULL);
		disk[fd] = joined;
		if (ft_isinnl(fd, disk) != -1)
			break ;
		len = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (make_line(fd, disk, len));
}
