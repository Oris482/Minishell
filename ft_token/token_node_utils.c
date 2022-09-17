/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:59:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:34:40 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_token.h"
#include "ft_alloc.h"

t_lx_token	*make_token_node(char *token_str, int token_type)
{
	t_lx_token *token;

	token = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
	token->token_str = token_str;
	token->token_type = token_type;
	return (token);
}

char	*get_token_str(const t_lx_token *token)
{
	if (token->interpret_symbol)
		return (token->interpreted_str);
	return (token->token_str);
}

t_lx_token	*get_last_token(t_lx_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->prev;
	return (token);
}
