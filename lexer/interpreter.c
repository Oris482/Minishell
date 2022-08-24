/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 16:36:25 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "lexer.h"

static void	_dollar_translater(t_lx_token *cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	find_str = getenv(chunk);
	if (!find_str || !*find_str)						// 해당 환경 변수가 없다면
		return ;
	str_cur = find_str;
	while (*str_cur)
	{
		if (split_flag && ft_isspace(*str_cur))
			break ;						// 처음 노드까지만 찾기
		str_cur++;
	}
	ft_strjoin_self(&cur->interpreted_str, ft_strcpy(find_str, str_cur));
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		cur->next = (t_lx_token *)calloc(1, sizeof(t_lx_token));
		find_str = str_cur;
		while (*str_cur && !ft_isspace(*str_cur))
			str_cur++;
		cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		cur = cur->next;
	}
}


static void	_dquote_translater(t_lx_token *cur, char *chunk)
{
	char	*pos;

	pos = ft_strchr_null(chunk, '$');
	ft_strjoin_self(&cur->interpreted_str, ft_strcpy(chunk, pos));
	chunk = pos;
	if (*chunk == '$')
		dollar_translater(cur, ++chunk, 0);
	return ;
}

static void	_interpret_middleware(t_lx_token *token, char *chunk, unsigned char symbol_type)
{
	if (symbol_type == UNDEFINED || symbol_type == QUOTE)
		ft_strjoin_self(&token->interpreted_str, chunk);
	else if (symbol_type == DQUOTE)
		_dquote_translater(token, chunk);
	else if (symbol_type == DOLLAR)
		_dollar_translater(token, chunk, 1);
	return ;
}

static unsigned char	_find_interpret_symbol(char **token_str, unsigned char target)
{
	if (target == UNDEFINED || target == DOLLAR)
	{
		while (**token_str && **token_str != '\'' && \
				**token_str != '\"' && **token_str != '$')
			(*token_str)++;
		return (is_quote(**token_str) | is_env_prefix(**token_str));
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
	char			*str_startpoint;
	unsigned char	symbol_type;
	char			*str_chunk;

	if (!token->interpret_symbol)
		return ;
	token_str = token->token_str;
	while (*token_str)
	{
		str_startpoint = token_str;
		symbol_type = UNDEFINED;
		if (is_quote(*str_startpoint) | is_env_prefix(*str_startpoint))
		{
			symbol_type = _find_interpret_symbol(&token_str, UNDEFINED);
			token_str++;
			_find_interpret_symbol(&token_str, symbol_type);
			str_chunk = ft_strcpy(str_startpoint + 1, token_str);
			if ((symbol_type == QUOTE || symbol_type == DQUOTE) && is_quote(*token_str))
				token_str++;
		}
		else
		{
			_find_interpret_symbol(&token_str, UNDEFINED);
			str_chunk = ft_strcpy(str_startpoint, token_str);
		}
		_interpret_middleware(token, str_chunk, symbol_type);
		while (token->next)
			token = token->next;
	}
}
