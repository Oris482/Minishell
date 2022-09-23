/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 12:30:15 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_check.h"

void	set_quote_flag(const char c, int *quote_flag)
{
	if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
		*quote_flag ^= QUOTE;
	else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
		*quote_flag ^= DQUOTE;
}

void	set_parentheses_flag(const char c, int *parentheses_flag, \
								int *quote_flag)
{
	if (!*quote_flag)
		*parentheses_flag += (c == '(') - (c == ')');
}

void	set_token_type(t_lx_token *token_node, char c)
{
	if (token_node->token_type == UNDEFINED)
	{
		token_node->token_type = is_token_seperator(c);
		if (token_node->token_type == UNDEFINED)
			token_node->token_type = WORD;
	}
}

void	set_interpret_symbol(t_lx_token *token_node)
{
	const char	*token_str = token_node->token_str;
	int			quote_flag;
	int			idx;
	char		c;

	quote_flag = FALSE;
	idx = 0;
	while (token_str && token_str[idx])
	{
		c = token_str[idx];
		if (!quote_flag && is_quote(c))
			token_node->interpret_symbol |= quote_flag;
		if (is_quote(c) == quote_flag)
			token_node->interpret_symbol |= quote_flag;
		if (!quote_flag || quote_flag == DQUOTE)
			token_node->interpret_symbol |= is_dollar(c);
		if (!quote_flag)
		{
			token_node->interpret_symbol |= is_wildcard(c);
			token_node->interpret_symbol |= is_tilde(c);
		}
		idx++;
	}
}

void	set_need_translate_symbol(t_lx_token *token_node, char c, \
									int *quote_flag)
{
	if (is_quote(c) && is_quote(c) == *quote_flag)
		token_node->interpret_symbol |= NEED_TRANSLATE;
	if ((!*quote_flag || *quote_flag == DQUOTE) && is_dollar(c))
		token_node->interpret_symbol |= NEED_TRANSLATE;
	if (!*quote_flag && is_wildcard(c))
		token_node->interpret_symbol |= NEED_TRANSLATE;
	if (!*quote_flag && is_tilde(c))
		token_node->interpret_symbol |= NEED_TRANSLATE;
}
