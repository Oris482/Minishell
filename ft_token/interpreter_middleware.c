/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_middleware.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 01:21:44 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_environ.h"

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
	char	*temp;

	if (*chunk == '?')
	{
		temp = ft_itoa(get_exit_status());
		ft_strjoin_self(&cur->interpreted_str, temp);
		ft_strjoin_self(&cur->interpreted_str, chunk + 1);
		my_free(temp);
		return ;
	}
	if (*chunk == '$')
	{
		ft_strjoin_self(&cur->interpreted_str, "$");
		ft_strjoin_self(&cur->interpreted_str, chunk);
		return ;
	}
	if (*chunk == '\0')
	{
		ft_strjoin_self(&cur->interpreted_str, "$");
		return ;
	}
	find_str = my_getenv(chunk);
	if (!find_str || !*find_str)
		return ;
	str_cur = find_str;
	if (split_flag && _cursor_to_space(&str_cur))
		;
	while (*str_cur)
		str_cur++;
	temp = ft_strcpy(find_str, str_cur);
	ft_strjoin_self(&cur->interpreted_str, temp);
	my_free(temp);
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		if (cur->interpret_symbol & WILDCARD)
			wildcard_translator(&cur);
		cur->next = make_token_node(NULL, WORD);
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

	while (*chunk)
	{
		pos = ft_strchr_null(chunk, '$');
		tmp = ft_strcpy(chunk, pos);
		ft_strjoin_self(&cur->interpreted_str, tmp);
		chunk = pos;
		my_free(tmp);
		if (*chunk == '$' && pos++)
		{
			while (*pos)
			{
				if (is_token_seperator(*pos) || is_interpret_symbol(*pos) || \
							(!is_dict_chr(*pos) && !is_number_chr(*pos)))
					break ;
				pos++;
			}
			tmp = ft_strcpy(chunk + 1, pos);
			_dollar_translator(cur, tmp, 0);
			my_free(tmp);
			chunk = pos;
		}
	}
}

static void	_tilde_translator(t_lx_token *cur, char *chunk)
{
	char	*env_home;

	env_home = NULL;
	if (is_tilde(*(cur->token_str)) && !cur->interpreted_str \
		&& (*(chunk + 1) == '\0' || *(chunk + 1) == '/'))
		env_home = my_getenv("HOME");
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
