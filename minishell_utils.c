/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 14:38:57 by jaesjeon         ###   ########.fr       */
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
		exit(1);
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
