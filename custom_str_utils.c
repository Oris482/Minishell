/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:57 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/31 15:56:21 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"

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

int	ft_strjoin_self(char **str, char *add)
{
	char	*new;
	int		len;

	if (!str | !add)
		return (ERROR);
	len = ft_strlen(*str) + ft_strlen(add) + 1;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (ERROR);
	ft_strlcpy(new, *str, len + 1);
	ft_strlcat(new, add, len + 1);
	if (*str)
		free(*str);
	*str = new;
	return (0);
}

char	*ft_strchr_null(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return ((char *)s + i);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s) + 1;
	while (size--)
		if (s[size] == (char)c)
			return ((char *)s + size);
	return (NULL);
}
