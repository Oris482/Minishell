/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 18:47:59 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"

unsigned char	find_interpret_symbol(char **token_str, \
												unsigned char target)
{
	if (target == UNDEFINED || target == DOLLAR)
	{
		while (**token_str && (!is_interpret_symbol(**token_str) \
							&& is_env_chr(**token_str, IDX_ONE_OR_MORE)))
			(*token_str)++;
		return (is_interpret_symbol(**token_str));
	}
	else if (target == TILDE)
	{
		while (**token_str && !is_dollar(**token_str) \
							&& !is_quote(**token_str))
			(*token_str)++;
		return (TILDE);
	}
	else
	{
		while ((is_quote(**token_str) | is_dollar(**token_str)) != target)
			(*token_str)++;
		return (target);
	}
}

static void	_interpret_middleware(t_lx_token *token, char *chunk, \
									unsigned char symbol_type)
{
	if (symbol_type == UNDEFINED || symbol_type == QUOTE)
		ft_strjoin_self(&token->interpreted_str, chunk);
	else if (symbol_type == TILDE && token->interpret_symbol & TILDE)
		tilde_translator(token, chunk);
	else if (symbol_type == DQUOTE)
		dquote_translator(token, chunk);
	else if (symbol_type == DOLLAR && token->interpret_symbol & DOLLAR)
	{
		if (*chunk == '\0' || is_tilde(*chunk))
		{
			ft_strjoin_self(&token->interpreted_str, "$");
			ft_strjoin_self(&token->interpreted_str, chunk);
			return ;
		}
		dollar_translator(token, chunk, 1);
	}
	else if (symbol_type == WILDCARD)
	{
		ft_strjoin_self(&token->interpreted_str, chunk);
		token->interpret_symbol |= WILDCARD;
	}
	return ;
}

static char	*_make_chunk_middleware(char **token_str, unsigned char *symbol_type)
{
	char	*str_startpoint;
	char	*str_chunk;

	str_startpoint = *token_str;
	*symbol_type = UNDEFINED;
	if (is_interpret_symbol(*str_startpoint))
		str_chunk = make_chunk_by_symbol(token_str, \
											str_startpoint, symbol_type);
	else
	{
		find_interpret_symbol(token_str, TILDE);
		str_chunk = ft_strcpy(str_startpoint, *token_str);
	}
	return (str_chunk);
}

void	interpreter(t_lx_token *token)
{
	char			*token_str;
	unsigned char	symbol_type;
	char			*str_chunk;

	token_str = token->token_str;
	while (*token_str)
	{
		str_chunk = _make_chunk_middleware(&token_str, &symbol_type);
		if (symbol_type == DOLLAR && ft_strlen(str_chunk) == 0 \
											&& is_quote(*token_str))
		{
			while (token->next)
				token = token->next;
			continue ;
		}
		_interpret_middleware(token, str_chunk, symbol_type);
		my_free(str_chunk);
		while (token->next)
			token = token->next;
	}
	if (token->interpret_symbol & WILDCARD)
		wildcard_translator(&token);
}
