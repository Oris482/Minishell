/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_translator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:01:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/23 13:34:54 by minsuki2         ###   ########.fr       */
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

char	*_cursor_to_space(int chunk_flag, char *str_cur)
{
	while (*str_cur)
	{
		if (!chunk_flag && ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}

static char	*_get_pos_dollar_name(char *next_str)
{
	int	i;

	i = 0;
	if (*next_str == '?')
		return (next_str + 1);
	while ((next_str)[i])
	{
		if (!is_env_chr(next_str[i], i))
			return (next_str + i);
		i++;
	}
	return (next_str + i);
}

static char	*_get_dollar_value(t_dict dict[], char *name)
{
	char	*ret_str;

	if (*name == '?')
	{
		ret_str = ft_itoa(get_exit_status());
		ft_strjoin_self(&ret_str, name + 1);
	}
	else
		ret_str = ft_strdup(my_getenv(dict, name));
	if (!ret_str || !*ret_str)
	{
		my_multi_free(name, ret_str, NULL, NULL);
		return (NULL);
	}
	my_free(name);
	return (ret_str);
}

static char	*_making_next_token_dollar_func(t_lx_token *cur_token, char *pos, \
																int chunk_flag)
{
	char	*cur_value;

	while (*pos)
	{
		if (ft_isspace(*pos) && pos++)
			continue ;
		cur_value = pos;
		pos = _cursor_to_space(!chunk_flag, cur_value);
		cur_token->next = make_token_node(NULL, WORD);
		cur_token = cur_token->next;
		cur_token->interpreted_str = ft_strcpy(cur_value, pos);
		cur_token->interpret_symbol |= DOLLAR * !chunk_flag \
				| WILDCARD * !!ft_strchr(cur_token->interpreted_str, '*');
		cur_value = pos;
	}
	return (pos);
}

#include "../ft_check/ft_check.h"

int	dollar_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str, \
												unsigned char symbol_type)
{
	const int	chunk_flag = (symbol_type == (DQUOTE | DOLLAR));
	int			ret;
	char		*value;
	char		*cur_value;
	char		*pos;

	if (*(*cur_str + 1) == '\0' || ft_isspace(*(*cur_str + 1)))
		return (ERROR);
	if (!is_env_chr(*(*cur_str + 1), 0) \
			&& !is_quote(*(*cur_str + 1)) \
			&& !is_wildcard(*(*cur_str + 1)) \
			&& !is_question_mark(*(*cur_str + 1)))
		return (ERROR);
	if (chunk_flag && *(*cur_str + 1) == '\"')
		return (ERROR);
	pos = _get_pos_dollar_name(*cur_str + 1);
	value = _get_dollar_value(dict, ft_strcpy(*cur_str + 1, pos));
	*cur_str = pos;
	if (!value)
		return (NOT_SPERATE);
	cur_value = value;
	if (!chunk_flag && !cur_token->interpreted_str)
		while (*cur_value && ft_isspace(*cur_value) && cur_value++)
			;
	pos = _cursor_to_space(!chunk_flag, cur_value);
	if (!ft_isspace(*cur_value))
		ft_strjoin_self_add_free(&cur_token->interpreted_str, \
													ft_strcpy(cur_value, pos));
	cur_token->interpret_symbol |= DOLLAR * !chunk_flag \
			| WILDCARD * !!ft_strchr(cur_token->interpreted_str, '*');
	cur_value = _making_next_token_dollar_func(cur_token, pos, !chunk_flag);
	ret = !!(ft_isspace(*(cur_value - 1)));
	my_free(value);
	return (ret);
}
