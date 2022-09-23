/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tilde_translator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/23 14:11:19 by minsuki2         ###   ########.fr       */
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

int	quote_translator(t_lx_token *cur_token, char **cur_str)
{
	char	*end;

	(*cur_str)++;
	end = ft_strchr(*cur_str, '\'');
	ft_strjoin_self_add_free(&cur_token->interpreted_str, \
											ft_strcpy(*cur_str, end));
	(*cur_str) = end + 1;
	cur_token->interpret_symbol |= QUOTE;
	return (NOT_SPERATE);
}

int	dquote_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str)
{
	char	*end;
	int		symbol_type;

	(*cur_str)++;
	end = ft_strchr(*cur_str, '\"');
	while (*cur_str != end)
	{
		symbol_type = is_interpret_symbol(**cur_str);
		interpret_middleware(dict, cur_token, cur_str, \
										symbol_type | DQUOTE * !!symbol_type);
	}
	*cur_str = end + 1;
	cur_token->interpret_symbol |= DQUOTE;
	return (NOT_SPERATE);
}

int	tilde_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str)
{
	if (!cur_token->token_str || cur_token->interpreted_str)
		return (ERROR);
	else if (*(cur_token->token_str + 1) != '\0' \
										&& *(cur_token->token_str + 1) != '/')
		return (ERROR);
	ft_strjoin_self(&cur_token->interpreted_str, my_getenv(dict, "HOME"));
	(*cur_str)++;
	cur_token->interpret_symbol |= TILDE;
	return (NOT_SPERATE);
}
