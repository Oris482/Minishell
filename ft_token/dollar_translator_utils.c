/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_translator_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:51:25 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/23 14:10:10 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_string.h"
#include "ft_check.h"

void check_dollar_wildcard_symbol(t_lx_token *cur_token, int chunk_flag)
{
	if (!chunk_flag)
		cur_token->interpret_symbol |= DOLLAR;
	if (ft_strchr(cur_token->interpreted_str, '*'))
		cur_token->interpret_symbol |= WILDCARD;
}

char	*cursor_to_space(int chunk_flag, char *str_cur)
{
	while (*str_cur)
	{
		if (!chunk_flag && ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}
