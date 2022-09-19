/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:18:47 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 15:43:24 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_check.h"

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (SPACE_SET);
	return (FALSE);
}

unsigned char	is_target_char(const char c, const char target)
{
	if (c == target)
		return (TRUE);
	return (FALSE);
}

int	is_metacharacter(const char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '(')
		return (PARENTHESES_OPEN);
	else if (c == ')')
		return (PARENTHESES_CLOSE);
	else if (c == '<')
		return (RED_IN);
	else if (c == '>')
		return (RED_OUT);
	else
		return (FALSE);
}

int	is_token_seperator(const char c)
{
	return (ft_isspace(c) | is_metacharacter(c));
}

int	is_redi_token(t_lx_token *token)
{
	const int	type = token->token_type;

	if (type == RED_IN || type == RED_OUT || type == HERE_DOC \
											|| type == RED_APD_OUT)
		return (TRUE);
	return (FALSE);
}
