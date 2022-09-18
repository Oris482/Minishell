/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:27:25 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 00:33:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"

int	print_export(void)
{
	int		idx;
	t_dict	*cur;

	idx = 0;
	while (idx < DICT_MAX)
	{
		cur = &g_dict[idx];
		while (cur->next)
		{
			cur = cur->next;
			ft_putstr_fd(EXPORT_HEAD_MSG, STDOUT_FILENO);
			ft_putstr_fd(cur->name, STDOUT_FILENO);
			if (cur->value)
			{
				ft_putstr_fd(cur->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		idx++;
	}
	return (SUCCESS_EXIT_CODE);
}

void	print_env(void)
{
	int		idx;
	t_dict	*cur;

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
}
