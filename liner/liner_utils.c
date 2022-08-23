/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:13:08 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 10:36:29 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liner.h"
#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char const *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len + 1 > dstsize)
		return (src_len + dstsize);
	if (dst_len + src_len + 1 < dstsize)
		dstsize = src_len + dst_len + 1;
	dst[dstsize - 1] = '\0';
	while (dstsize-- - 1 > dst_len)
		dst[dstsize - 1] = src[dstsize - dst_len - 1];
	return (dst_len + src_len);
}

size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize > 0)
	{
		if (len + 1 < dstsize)
			dstsize = len + 1;
		dst[dstsize - 1] = '\0';
		while (dstsize-- - 1)
			dst[dstsize - 1] = src[dstsize - 1];
	}
	return (len);
}

int ft_strjoin_self(char **str, char *add)
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
