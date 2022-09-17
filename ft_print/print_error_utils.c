/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:12:42 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:32:13 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void print_error_not_close(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error not close token`", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void print_error_syntax(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token`", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

int	print_error_str(const char *err_cmd, const char *err_arg, \
							const char *custom_msg, int err_code)
{
	const char	*err_msg = strerror(errno);

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err_arg != NULL)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(err_arg, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (custom_msg == NULL)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	else
		ft_putendl_fd(custom_msg, STDERR_FILENO);
	return (err_code);
}
