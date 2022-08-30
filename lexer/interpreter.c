/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/30 23:34:21 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "myfunc.h"

static void	_dollar_translator(t_lx_token *cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	find_str = getenv(chunk);
	if (!find_str || !*find_str)
		return ;
	str_cur = find_str;
	while (*str_cur)
	{
		if (split_flag && ft_isspace(*str_cur))
			break ;
		str_cur++;
	}
	ft_strjoin_self(&cur->interpreted_str, ft_strcpy(find_str, str_cur));
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		if (cur->interpret_symbol & WILDCARD)
			wildcard_translator(&cur);
		cur->next = (t_lx_token *)calloc(1, sizeof(t_lx_token));
		find_str = str_cur;
		while (*str_cur && !ft_isspace(*str_cur))
			str_cur++;
		cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		if (split_flag)
			cur->next->interpret_symbol = DOLLAR;
		cur = cur->next;
	}
}

static void	_dquote_translator(t_lx_token *cur, char *chunk)
{
	char	*pos;

	pos = ft_strchr_null(chunk, '$');
	ft_strjoin_self(&cur->interpreted_str, ft_strcpy(chunk, pos));
	chunk = pos;
	if (*chunk == '$')
		_dollar_translator(cur, ++chunk, 0);
	return ;
}

static void	_tilde_translator(t_lx_token *cur, char *chunk)
{
	char	*env_home;
	size_t	len;

	env_home = NULL;
	if (is_tilde(*(cur->token_str)) \
		&& (*(chunk + 1) == '\0' || *(chunk + 1) == '/'))
		env_home = getenv("HOME");
	printf("env_home = %s\n", chunk);
	if (env_home != NULL)
		chunk++;
	len = ft_strlen(chunk) - 1 + ft_strlen(env_home);
	cur->interpreted_str = ft_strsjoin(env_home, chunk, NULL);
	return ;
}

static void	_interpret_middleware(t_lx_token *token, char *chunk, \
									unsigned char symbol_type)
{
	if (symbol_type == UNDEFINED || symbol_type == QUOTE)
		ft_strjoin_self(&token->interpreted_str, chunk);
	else if (symbol_type == TILDE && token->interpret_symbol & TILDE)
		_tilde_translator(token, chunk);
	else if (symbol_type == DQUOTE)
		_dquote_translator(token, chunk);
	else if (symbol_type == DOLLAR && token->interpret_symbol & DOLLAR)
	{
		if (is_tilde(*chunk))
		{
			token->interpret_symbol &= ~TILDE;
			ft_strjoin_self(&token->interpreted_str, "$");
			ft_strjoin_self(&token->interpreted_str, chunk);
			return ;
		}
		_dollar_translator(token, chunk, 1);
	}
	else if (symbol_type == WILDCARD)
			ft_strjoin_self(&token->interpreted_str, chunk);
	return ;
}

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
		while (**token_str && !is_env_prefix(**token_str) \
							&& !is_quote(**token_str))
			(*token_str)++;
		return (TILDE);
	}
	else
	{
		while ((is_quote(**token_str) | is_env_prefix(**token_str)) != target)
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
		_interpret_middleware(token, str_chunk, symbol_type);
		my_free(str_chunk);
		while (token->next)
			token = token->next;
	}
	if (token->interpret_symbol & WILDCARD)
		wildcard_translator(&token);
}
