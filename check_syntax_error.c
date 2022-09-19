/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:24:20 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/20 00:26:13 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_command.h"

unsigned int	check_syntax_error(t_lx_token *cur_node)
{
	int			parentheses_counter;

	parentheses_counter = 0;
	while (cur_node)
	{
		if (cur_node->token_type == PARENTHESES_OPEN)
			parentheses_counter++;
		else if (cur_node->token_type == PARENTHESES_CLOSE)
			parentheses_counter--;
		if (check_syntax_middleware(cur_node, &parentheses_counter) == FALSE)
			return (SYNTAX_ERROR_EXIT_CODE);
		if (cur_node->token_type == HERE_DOC)
			if (make_tmp_heredoc(cur_node, cur_node->next->token_str) != \
															SUCCESS_EXIT_CODE)
				return (GENERAL_EXIT_CODE);
		cur_node = cur_node->next;
	}
	return (SUCCESS_EXIT_CODE);
}
