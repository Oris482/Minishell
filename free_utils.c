/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:48:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 17:49:49 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "lexer.h"
#include "parser.h"

t_lx_token *lst_fclean(t_lx_token *cur_list)
{
	while (cur_list)
	{
		my_multi_free(cur_list->token_str, cur_list->interpreted_str, \
															cur_list, NULL);
		cur_list = cur_list->next;
	}
	return (NULL);
}

void tree_free(t_tree *cur_tree)
{
	lst_fclean(cur_tree->token_data);
	my_multi_free(cur_tree, NULL, NULL, NULL);
}