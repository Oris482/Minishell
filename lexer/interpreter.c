/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 21:59:00 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"


void interpret_middleware(t_lx_token *token)
{
	if ()

	str
	lst

}

void	interpreter(t_lx_token *token_head, char *envp[])
{
	t_lx_token	*cur_node;

	cur_node = token_head;
	while (cur_node)
	{
		if (cur_node->interpret_symbol)
			interpret_middleware(cur_node);		//node까지?
		cur_node = cur_node->next;
	}
}
