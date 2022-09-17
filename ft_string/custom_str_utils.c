/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:57 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:28:58 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_alloc.h"

size_t	ft_strcnt(const char *s, const char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			cnt++;
		s++;
	}
	return (cnt);
}

char	*ft_strsjoin(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	char	*start;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	ret = (char *)my_malloc(sizeof(char) * (len + 1));
	start = ret;
	while (s1 && *s1)
		*ret++ = *s1++;
	while (s2 && *s2)
		*ret++ = *s2++;
	while (s3 && *s3)
		*ret++ = *s3++;
	*ret = '\0';
	return (start);
}

char	*ft_strjoin_self(char **str, char *add)
{
	char	*new;
	int		len;

	if (!str || !add)
		return (NULL);
	len = ft_strlen(*str) + ft_strlen(add) + 1;
	new = (char *)my_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(new, *str, len + 1);
	ft_strlcat(new, add, len + 1);
	my_free(*str);
	*str = new;
	return (*str);
}

char	*ft_strchr_null(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return ((char *)s + i);
}

char	*ft_strrchr_right_away(const char *s, int c, char *const end)
{
	while (s >= end)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
