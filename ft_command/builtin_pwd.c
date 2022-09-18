/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:48:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 22:13:35 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_alloc.h"
#include "ft_string.h"
#include "ft_token.h"

int	_handle_pwd_error(void)
{
	char	*err_msg;

	err_msg = NULL;
	if (errno == ENOENT)
		err_msg = "Current working directory is no more exist";
	else if (errno == ENOMEM)
		err_msg = "Insufficient memory to store cwd";
	else if (errno == EACCES)
		err_msg = "Permission denied";
	return (print_error_str("pwd", NULL, err_msg, GENERAL_EXIT_CODE));
}

int	builtin_pwd(t_lx_token *token)
{
	t_lx_token			*arg_token;
	char				*buf;

	buf = NULL;
	arg_token = token;
	if (builtin_option_arg_checker(&token) == OPTION_ERROR)
		return (print_error_str("pwd", get_token_str(arg_token), \
					"invalid option", INVALID_OPTION_EXIT_CODE));
	buf = getcwd(buf, 1);
	if (buf == NULL)
		return (_handle_pwd_error());
	ft_putendl_fd(buf, STDOUT_FILENO);
	my_free(buf);
	return (SUCCESS_EXIT_CODE);
}
