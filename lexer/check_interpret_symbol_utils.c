/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_interpret_symbol_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:09:05 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/01 15:51:09 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	is_quote(const char c)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DQUOTE);
	return (FALSE);
}

unsigned char	is_dollar(const char c)
{
	if (c == '$')
		return (DOLLAR);
	return (FALSE);
}

unsigned char	is_wildcard(const char c)
{
	if (c == '*')
		return (WILDCARD);
	return (FALSE);
}

unsigned char	is_tilde(const char c)
{
	if (c == '~')
		return (TILDE);
	return (FALSE);
}

unsigned char	is_interpret_symbol(const char c)
{
	return (is_quote(c) | is_dollar(c) | is_wildcard(c) | is_tilde(c));
}
