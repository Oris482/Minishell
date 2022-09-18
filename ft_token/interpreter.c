/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 02:07:33 by minsuki2         ###   ########.fr       */
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
					&& is_env_chr(**token_str, 1)))
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

static void	_make_chunk_middleware(char **str_startpoint, char **token_str, \
								char **str_chunk, unsigned char *symbol_type)
{
	*str_startpoint = *token_str;
	*symbol_type = UNDEFINED;
	if (is_interpret_symbol(**str_startpoint))
		*str_chunk = make_chunk_by_symbol(token_str, \
											*str_startpoint, symbol_type);
	else
	{
		find_interpret_symbol(token_str, TILDE);
		*str_chunk = ft_strcpy(*str_startpoint, *token_str);
	}
}

void	interpreter(t_lx_token *token)
{
	char			*token_str;
	unsigned char	symbol_type;
	char			*str_startpoint;
	char			*str_chunk;

	token_str = token->token_str;
	while (*token_str)
	{
		_make_chunk_middleware(&str_startpoint, &token_str, \
										&str_chunk, &symbol_type);
		if (symbol_type == DOLLAR && ft_strlen(str_chunk) == 0 \
											&& is_quote(*token_str))
		{
			while (token->next)
				token = token->next;
			continue ;
		}
		interpret_middleware(token, str_chunk, symbol_type);
		my_free(str_chunk);
		while (token->next)
			token = token->next;
	}
	if (token->interpret_symbol & WILDCARD)
		wildcard_translator(&token);
}
