/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 21:12:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_parentheses_flag(const char c, unsigned char *parentheses_flag
		, unsigned char *quote_flag)
{
	if (!*quote_flag)									// 통일성을 위해 주소로?
	{
		if (c == '(' && !*parentheses_flag)
			*parentheses_flag ^= PARENTHESES_OPEN;
		else if (c == ')')
			if (*parentheses_flag == PARENTHESES_OPEN)
				*parentheses_flag ^= PARENTHESES_OPEN;
	}
}

void	set_quote_flag(const char c, unsigned char *quote_flag)
{
	if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
		*quote_flag ^= QUOTE;
	else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
		*quote_flag ^= DQUOTE;
}

char	*ft_strcpy(const char *start, const char *end)
{
	char	*ret;
	size_t	len;
	int		idx;

	len = end - start;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		exit(GENERAL_EXIT_CODE);
	idx = 0;
	while (idx < (int)len)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

unsigned char	is_quote(const char c)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DQUOTE);
	return (FALSE);
}

unsigned char	is_env_prefix(const char c)
{
	if (c == '$')
		return (DOLLAR);
	return (FALSE);
}

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (SPACE_SET);
	return (FALSE);
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