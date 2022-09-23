/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_translator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:01:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/23 17:19:15 by jaesjeon         ###   ########.fr       */
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

static char	*_editing_now_token_in_dollar(t_lx_token *cur_token, char *value, \
																int chunk_flag)
{
	char	*cur_value;
	char	*pos;

	cur_value = value;
	if (!chunk_flag && !cur_token->interpreted_str)
		while (*cur_value && ft_isspace(*cur_value) && cur_value++)
			;
	pos = cursor_to_space(chunk_flag, cur_value);
	if (!ft_isspace(*cur_value))
		ft_strjoin_self_add_free(&cur_token->interpreted_str, \
													ft_strcpy(cur_value, pos));
	check_dollar_wildcard_symbol(cur_token, chunk_flag);
	return (pos);
}

static char	*_making_next_token_in_dollar(t_lx_token *cur_token, char *pos, \
																int chunk_flag)
{
	char	*cur_value;

	while (*pos)
	{
		if (ft_isspace(*pos) && pos++)
			continue ;
		cur_value = pos;
		pos = cursor_to_space(chunk_flag, cur_value);
		cur_token->next = make_token_node(NULL, WORD);
		cur_token->next->interpreted_str = ft_strcpy(cur_value, pos);
		check_dollar_wildcard_symbol(cur_token->next, chunk_flag);
		cur_token = cur_token->next;
		cur_value = pos;
	}
	return (pos);
}

int	dollar_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str, \
												unsigned char symbol_type)
{
	const int	chunk_flag = (symbol_type == (DQUOTE | DOLLAR));
	int			ret;
	char		*value;
	char		*pos;

	if (check_not_dollar_translator(*cur_str + 1, chunk_flag) == ERROR)
		return (ERROR);
	pos = _get_pos_dollar_name(*cur_str + 1);
	value = _get_dollar_value(dict, ft_strcpy(*cur_str + 1, pos));
	*cur_str = pos;
	if (!value)
		return (NOT_SPERATE);
	pos = _editing_now_token_in_dollar(cur_token, value, chunk_flag);
	pos = _making_next_token_in_dollar(cur_token, pos, chunk_flag);
	ret = !!(ft_isspace(*(pos - 1)));
	my_free(value);
	return (ret);
}
