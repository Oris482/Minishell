/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:19:28 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 02:43:26 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_lx_token *token)
{
	int	no_newline_option;

	no_newline_option = FALSE;
	token = token->next;
	if (token && ft_strcmp("-n", get_token_str(token)) == SUCCESS)
	{
		no_newline_option = TRUE;
		token = token->next;
	}
	while (token)
	{
		ft_putstr_fd(get_token_str(token), STDOUT_FILENO);
		token = token->next;
		if (token)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!no_newline_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS_EXIT_CODE);
}
