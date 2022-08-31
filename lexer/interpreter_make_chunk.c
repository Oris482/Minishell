/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_make_chunk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:24:18 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/31 15:43:49 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static char	*_handle_quote_symbol(char **token_str, char *str_startpoint, \
								unsigned char *symbol_type)
{
	char	*str_chunk;

	str_chunk = ft_strcpy(str_startpoint + 1, *token_str);
	if ((*symbol_type == QUOTE || *symbol_type == DQUOTE) \
								&& is_quote(**token_str))
		(*token_str)++;
	return (str_chunk);
}

static char	*_handle_dollar_symbol(char **token_str, char *str_startpoint)
{
	if (is_tilde(**token_str))
		find_interpret_symbol(token_str, TILDE);
	else
		find_interpret_symbol(token_str, DOLLAR);
	return (ft_strcpy(str_startpoint + 1, *token_str));
}

static char	*_handle_tilde_symbol(char **token_str, char *str_startpoint)
{
	while (**token_str && !is_quote(**token_str) && !is_env_prefix(**token_str))
		(*token_str)++;
	return (ft_strcpy(str_startpoint, *token_str));
}

static char	*_handle_wildcard_symbol(char **token_str, char *str_startpoint)
{
	while (**token_str && is_wildcard(**token_str))
		(*token_str)++;
	return (ft_strcpy(str_startpoint, *token_str));
}

char	*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type)
{
	*symbol_type = find_interpret_symbol(token_str, UNDEFINED);
	(*token_str)++;
	if (is_quote(*str_startpoint))
		return (_handle_quote_symbol(token_str, str_startpoint, symbol_type));
	else if (is_env_prefix(*str_startpoint))
		return (_handle_dollar_symbol(token_str, str_startpoint));
	else if (is_tilde(*str_startpoint))
		return (_handle_tilde_symbol(token_str, str_startpoint));
	else if (is_wildcard(*str_startpoint))
		return (_handle_wildcard_symbol(token_str, str_startpoint));
	else
		return (NULL);
}
