/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_middleware.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 16:25:25 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_environ.h"

static char	*_cursor_to_space(int split_flag, char *str_cur)
{
	while (*str_cur)
	{
		if (split_flag && ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}

static void	_dollar_translator(t_lx_token *token_cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;
	// char	*temp;

	if (*chunk == '?')
		find_str = ft_itoa(get_exit_status());
	else
		find_str = my_getenv(chunk);
	// {
	//     // ft_strjoin_self(&token_cur->interpreted_str, temp);
	//     // ft_strjoin_self(&token_cur->interpreted_str, chunk + 1);
	//     // my_free(temp);
	//     // return ;
	// }
	// if (*chunk == '$')
	// {
	//     ft_strjoin_self(&token_cur->interpreted_str, "$");
	//     ft_strjoin_self(&token_cur->interpreted_str, chunk);
	//     return ;
	// }
	// if (*chunk == '\0')
	// {
	//     ft_strjoin_self(&token_cur->interpreted_str, "$");
	//     return ;
	// }
	if (!find_str || !*find_str)
		return ;
	str_cur = _cursor_to_space(split_flag, find_str);
	ft_strjoin_self_add_free(&token_cur->interpreted_str, \
												ft_strcpy(find_str, str_cur));
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		if (token_cur->interpret_symbol & WILDCARD)
			wildcard_translator(&token_cur);
		find_str = str_cur;
		str_cur = _cursor_to_space(split_flag, find_str);
		token_cur->next = make_token_node(NULL, WORD);
		token_cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		token_cur->next->interpret_symbol |= DOLLAR * split_flag \
			| WILDCARD * !!ft_strchr(token_cur->next->interpreted_str, '*');
		token_cur = token_cur->next;
	}
}

static void	_dquote_translator(t_lx_token *cur, char *chunk)
{
	char	*pos;
	char	*tmp;

	while (*chunk)
	{
		pos = ft_strchr_null(chunk, '$');
		ft_strjoin_self_add_free(&cur->interpreted_str, \
													ft_strcpy(chunk, pos));
		chunk = pos;
		if (*chunk == '$' && pos++)
		{
			while (*pos)
			{
				if (is_token_seperator(*pos) || is_interpret_symbol(*pos) \
								|| (!is_env_chr(*pos, IDX_ONE_OR_MORE) \
												&& !is_question_mark(*pos)))
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
