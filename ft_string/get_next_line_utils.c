/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:43:17 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 17:13:25 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;
	size_t	idx;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc(s1_len + s2_len + 1);
	if (joined == NULL)
		return (NULL);
	idx = 0;
	while (s1_len > 0)
	{
		joined[idx++] = *s1++;
		s1_len--;
	}
	while (s2_len > 0)
	{
		joined[idx++] = *s2++;
		s2_len--;
	}
	joined[idx] = '\0';
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	str_len;
	size_t	idx;

	str_len = ft_strlen(s);
	if ((str_len - start) < len && str_len > start)
		len = str_len - start;
	else if (str_len <= start)
		len = 0;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	if (start >= str_len)
	{
		*sub = '\0';
		return (sub);
	}
	idx = 0;
	while (s[start] != '\0' && len > 0)
	{
		sub[idx++] = s[start++];
		len--;
	}
	sub[idx] = '\0';
	return (sub);
}

int	ft_isinnl(int fd, char **disk)
{
	int	idx;

	idx = 0;
	while (disk[fd][idx])
	{
		if (disk[fd][idx] == 10)
			return (idx);
		idx++;
	}
	return (-1);
}
