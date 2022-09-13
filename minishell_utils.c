/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/13 18:29:10 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"

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

t_dict	*get_last_dict(t_dict *dic)
{
	if (!dic)
		return (NULL);
	while (dic->next)
		dic = dic->prev;
	return (dic);
}

t_dict	*get_first_dict(t_dict *dic)
{
	if (!dic)
		return (NULL);
	while (dic->prev->next)
		dic = dic->prev;
	return (dic);
}

void	*make_new_node(size_t size)
{
	void	*new;

	new = my_calloc(1, size);
	return (new);
}

t_lx_token	*make_new_token(char *token_str, int token_type, t_lx_token *prev)
{
	t_lx_token *token;

	token = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
	token->token_str = token_str;
	token->token_type = token_type;
	token->prev = prev;
	return (token);
}
