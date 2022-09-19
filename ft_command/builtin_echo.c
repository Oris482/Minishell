/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:19:28 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 04:50:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_string.h"
#include "ft_token.h"
#include "ft_print.h"

void	handle_echo_option(t_lx_token **token, int *option)
{
	char	*str;
	int		idx;

	while (*token)
	{
		idx = 2;
		str = get_token_str(*token);
		if (str && str[0] && str[0] == '-' && str[1] && str[1] == 'n')
		{
			while (str[idx] && str[idx] == 'n')
				idx++;
			if (str[idx] == '\0')
			{
				*token = (*token)->next;
				*option |= TRUE;
			}
			else
				break ;
		}
		else
			break ;
	}
}

int	builtin_echo(t_lx_token *token)
{
	int	no_newline_option;

	no_newline_option = FALSE;
	token = token->next;
	handle_echo_option(&token, &no_newline_option);
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
