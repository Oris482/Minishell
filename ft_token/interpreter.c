/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 00:55:23 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"


static int	_interpret_middleware_is_sperated(t_lx_token *cur_token, \
			char **cur_token_str, unsigned char symbol_type)
{
	if (symbol_type == UNDEFINED || symbol_type == QUOTE)
		return (qutoe_translator(cur_token, cur_token_str));
	else if (symbol_type == DQUOTE)
		return (dquote_translator(cur_token, cur_token_str));
	else if (symbol_type == DOLLAR)
		return (dollar_translator(cur_token, cur_token_str));
	else if (symbol_type == WILDCARD)
		return (wildcard_translator(&cur_token, cur_token_str));
	else if (symbol_type == TILDE)
		return (tilde_translator(cur_token, cur_token_str));
	return (ERROR);
}

void	interpreter(t_lx_token *cur_token)
{
	char			*cur_token_str;
	t_lx_token		*incomming_token;

	unsigned char	symbol_type;
	int				sperate_token_flag

	cur_token_str = token->token_str;
	while (*cur_token_str)
	{
		if (_interpret_middleware_is_sperated(cur_token, &cur_token_str, \
										is_interpret_symbol(*cur_token_str)))
			cur_token->next = make_token_node(NULL, WORD);
		while (cur_token->next)
			cur_token = cur_token->next;
	}
}
