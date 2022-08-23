/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 18:15:15 by minsuki2         ###   ########.fr       */
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
