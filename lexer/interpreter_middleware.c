/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_middleware.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 20:08:12 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_cursor_to_space(char **str_cur)
{
	while (**str_cur)
	{
		if (ft_isspace(**str_cur))
			break ;
		(*str_cur)++;
	}
	return (TRUE);
}

static void	_dollar_translator(t_lx_token *cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	// if (*chunk == '?')
	find_str = getenv(chunk);
	if (!find_str || !*find_str)
		return ;
	str_cur = find_str;
	if (split_flag && _cursor_to_space(&str_cur))
		;
	ft_strjoin_self(&cur->interpreted_str, ft_strcpy(find_str, str_cur));
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		if (cur->interpret_symbol & WILDCARD)
			wildcard_translator(&cur);
		cur->next = (t_lx_token *)make_new_node(sizeof(t_lx_token));
		find_str = str_cur;
		while (*str_cur && !ft_isspace(*str_cur))
			str_cur++;
		cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		if (ft_strchr(cur->next->interpreted_str, '*'))
			cur->next->interpret_symbol |= WILDCARD;
		if (split_flag)
			cur->next->interpret_symbol |= DOLLAR;
		cur = cur->next;
	}
}

static void	_dquote_translator(t_lx_token *cur, char *chunk)
{
	char	*pos;
	char	*tmp;

	pos = ft_strchr_null(chunk, '$');
	tmp = ft_strcpy(chunk, pos);
	ft_strjoin_self(&cur->interpreted_str, tmp);
	chunk = pos;
	my_free(tmp);
	if (*chunk == '$')
		_dollar_translator(cur, ++chunk, 0);
	return ;
}

static void	_tilde_translator(t_lx_token *cur, char *chunk)
{
	char	*env_home;

	env_home = NULL;
	if (is_tilde(*(cur->token_str)) && !cur->interpreted_str \
		&& (*(chunk + 1) == '\0' || *(chunk + 1) == '/'))
		env_home = getenv("HOME");
	if (env_home != NULL)
		chunk++;
	ft_strjoin_self(&cur->interpreted_str, env_home);
	ft_strjoin_self(&cur->interpreted_str, chunk);
	return ;
}

void	interpret_middleware(t_lx_token *token, char *chunk, \
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
		if (*chunk == '\0' || is_tilde(*chunk))
		{
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
