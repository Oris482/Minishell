/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:23:17 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/24 21:49:50 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_command.h"
#include "ft_token.h"
#include "ft_print.h"

static int	_is_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (FALSE);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		return (FALSE);
	return (TRUE);
}

static unsigned char	_ft_atouc(char *str)
{
	unsigned char	ret;
	char			sign;

	ret = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		ret = (ret << 1) + (ret << 3) + (*str - '0');
		str++;
	}
	ret *= sign;
	return (ret);
}

int	builtin_exit(t_lx_token *token)
{
	char			*token_str;
	unsigned char	exit_code;
	int				exit_code_flag;

	exit_code_flag = FALSE;
	if (token->next)
	{
		token_str = get_token_str(token->next);
		if (_is_numeric(token_str) == FALSE)
			return (print_error_str("exit", token_str, \
						"numeric argument required", NONE_NUMERIC_EXIT_CODE));
		else if (token->next->next != NULL)
			return (print_error_str("exit", NULL, \
						"too many arguments", GENERAL_EXIT_CODE));
		exit_code = _ft_atouc(token_str);
		exit_code_flag = TRUE;
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (exit_code_flag)
		exit(exit_code);
	exit(get_exit_status());
	return (exit_code);
}
