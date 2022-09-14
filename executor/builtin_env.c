/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:08:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/15 02:52:52 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include "minishell.h"

int	builtin_env(t_lx_token *token)
{
	int		idx;
	t_dict	*cur;

	if (token->next)
		return (GENERAL_EXIT_CODE);
	idx = 0;
	while (idx < DICT_MAX)
	{
		cur = &g_dict[idx];
		while (cur->next)
		{
			cur = cur->next;
			if (!cur->value)
				continue ;
			ft_putstr_fd(cur->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(cur->value, STDOUT_FILENO);
		}
		idx++;
	}
	return (SUCCESS_EXIT_CODE);
}
