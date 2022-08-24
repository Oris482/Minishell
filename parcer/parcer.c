/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:31:09 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 10:53:51 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "../lexer/lexer.h"
#include "../minishell.h"
// #include "minishell.h"



void recursive_tree()
{


}

int parcer(t_lx_token *head)
{
	t_tree		*point;
	t_lx_token	*cur_node;

	cur_node = head;
	while (cur_node)
	{
		is_metachracter();
		is_


		cur_node = cur_node->next;
	}
}

