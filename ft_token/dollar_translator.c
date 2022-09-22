/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_translator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:01:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/22 14:35:11 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_file.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_environ.h"

char	*_cursor_to_space(int split_flag, char *str_cur)
{
	while (*str_cur)
	{
		if (split_flag && ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}

static char	*_get_pos_dollar_chunk(char **cur_token_str)
{
	int	i;

	(*cur_token_str)++;
	i = 0;
	while ((*cur_token_str)[i])
	{
		if (!is_env_chr((*cur_token_str)[i], i))
			return ((*cur_token_str) + i);
		i++;
	}
	return ((*cur_token_str) + i);
}

static char	*_make_dollar_interpreted(char *chunk)
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
	{
		my_multi_free(chunk, ret_str, NULL, NULL);
		return (NULL);
	}
	my_free(chunk);
	return (ret_str);
}

static char	*_making_next_token_dollar_func(t_lx_token **cur_token, \
							char **cur_token_str, char *pos, int split_flag)
{
	char	*cur_value;

	while (*pos)
	{
		if (ft_isspace(*pos) && pos++)
			continue ;
		cur_value = pos;
		pos = _cursor_to_space(split_flag, cur_value);
		(*cur_token)->next = make_token_node(NULL, WORD);
		*cur_token = (*cur_token)->next;
		(*cur_token)->interpreted_str = ft_strcpy(cur_value, pos);
		// wildcard flag on && interpret
		(*cur_token)->interpret_symbol |= DOLLAR * split_flag \
				| WILDCARD * !!ft_strchr((*cur_token)->interpreted_str, '*');
		if ((*cur_token)->interpret_symbol & WILDCARD)
			interpret_wildcard_token(cur_token);
		//
		(void)cur_token_str;
		cur_value = pos;
	}
	return (pos);
}

int	dollar_translator(t_lx_token **cur_token, char **cur_token_str, \
												unsigned char symbol_type)
{
	const int	split_flag = !(symbol_type == (DQUOTE | DOLLAR));
	int			ret;
	char		*value;
	char		*cur_value;
	char		*pos;

	pos = _get_pos_dollar_chunk(cur_token_str);
	value = _make_dollar_interpreted(ft_strcpy(*cur_token_str, pos));
	*cur_token_str = pos;
	if (!value)
		return (NOT_SPERATE);
	cur_value = value;
	if (split_flag && !(*cur_token)->interpreted_str)
		while (*cur_value && ft_isspace(*cur_value) && cur_value++);
	pos = _cursor_to_space(split_flag, cur_value);
	if (!ft_isspace(*cur_value))
		ft_strjoin_self_add_free(&(*cur_token)->interpreted_str, \
													ft_strcpy(cur_value, pos));
	// wildcard flag on && interpret
	(*cur_token)->interpret_symbol |= DOLLAR * split_flag \
			| WILDCARD * !!ft_strchr((*cur_token)->interpreted_str, '*');
	if ((*cur_token)->interpret_symbol & WILDCARD)
		interpret_wildcard_token(cur_token);
	//
	cur_value = _making_next_token_dollar_func(cur_token, cur_token_str, \
															pos, split_flag);
	ret = !!(ft_isspace(*(cur_value - 1)));
	my_free(value);
	return (ret);
}
