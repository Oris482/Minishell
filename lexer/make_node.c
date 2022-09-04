/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:17:29 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/04 16:40:44 by jaesjeon         ###   ########.fr       */
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
		cur->next->prev = cur;
	else
		if (token_head)
			token_head->prev = cur;
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
