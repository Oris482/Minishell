/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_translator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:51:43 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 16:59:35 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_token.h"
#include "ft_environ.h"
#include "ft_alloc.h"

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

static char	*_cursor_to_not_space(char *str_cur)
{
	while (*str_cur)
	{
		if (!ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}

static char	*_make_dollar_find_str(char *chunk)
{
	char	*ret_str;

	if (*chunk == '?')
	{
		ret_str = ft_itoa(get_exit_status());
		ft_strjoin_self(&ret_str, chunk + 1);
	}
	else if (*chunk == '$' || *chunk == '\0')
		ret_str = ft_chr_to_str('$');
	else
		ret_str = ft_strdup(my_getenv(chunk));
	if (!ret_str || !*ret_str)
		return (NULL);
	return (ret_str);
}

static void	_dollar_translated_to_node(t_lx_token **token_cur, \
										char *find_str, char *str_cur)
{
	if ((*token_cur)->interpreted_str != NULL \
				&& ft_strlen((*token_cur)->interpreted_str) != 0)
	{
		(*token_cur)->next = make_token_node(NULL, WORD);
		(*token_cur) = (*token_cur)->next;
	}
	(*token_cur)->interpreted_str = ft_strcpy(find_str, str_cur);
	(*token_cur)->interpret_symbol = 0;
	(*token_cur)->interpret_symbol |= DOLLAR \
			| WILDCARD * !!ft_strchr((*token_cur)->interpreted_str, '*');
}

void	dollar_translator(t_lx_token *token_cur, \
								char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	find_str = _make_dollar_find_str(chunk);
	if (!find_str)
		return ;
	str_cur = _cursor_to_space(split_flag, find_str);
	ft_strjoin_self_add_free(&token_cur->interpreted_str, \
												ft_strcpy(find_str, str_cur));
	my_free(find_str);
	while (*str_cur)
	{
		str_cur = _cursor_to_not_space(str_cur);
		if (token_cur->interpret_symbol & WILDCARD)
			wildcard_translator(&token_cur);
		find_str = str_cur;
		str_cur = _cursor_to_space(split_flag, find_str);
		_dollar_translated_to_node(&token_cur, find_str, str_cur);
	}
}
