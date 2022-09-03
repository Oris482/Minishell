/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:17:29 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/03 23:11:54 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"
#include "../my_func/myfunc.h"

// t_lx_token *new_token()
// {
//     t_lx_token *new;
//
//     new = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
//     return (new);
// }

t_lx_token	*connect_token(t_lx_token *token_head, t_lx_token *cur)
{
	if (cur->next)
		cur->next->priv = cur;
	else
		if (token_head)
			token_head->priv = cur;
	return (cur->next);
}
// t_lx_token *add_token_back(t_lx_token *cur)
// {
//     t_lx_token *new;
//
//     new = (t_lx_token *)my_calloc(1, , sizeof(t_lx_token));
//     new->prev = cur;
//
//     return (new);
// }
