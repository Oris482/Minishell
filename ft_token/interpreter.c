/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "lexer.h"
#include "myfunc.h"

unsigned char	find_interpret_symbol(char **token_str, \
												unsigned char target)
{
	if (target == UNDEFINED || target == DOLLAR)
	{
		while (**token_str && !is_interpret_symbol(**token_str))
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

void	interpreter(t_lx_token *token)
{
	char			*token_str;
	unsigned char	symbol_type;
	char			*str_startpoint;
	char			*str_chunk;

	token_str = token->token_str;
	while (*token_str)
	{
		str_startpoint = token_str;
		symbol_type = UNDEFINED;
		if (is_interpret_symbol(*str_startpoint))
			str_chunk = make_chunk_by_symbol(&token_str, \
												str_startpoint, &symbol_type);
		else
		{
			find_interpret_symbol(&token_str, TILDE);
			str_chunk = ft_strcpy(str_startpoint, token_str);
		}
		interpret_middleware(token, str_chunk, symbol_type);
		my_free(str_chunk);
		while (token->next)
			token = token->next;
	}
	if (token->interpret_symbol & WILDCARD)
		wildcard_translator(&token);
}
