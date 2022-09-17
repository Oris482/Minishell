/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:48:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:23:44 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command.h"
#include "ft_print.h"
#include "ft_alloc.h"

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

int	builtin_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
		return (_handle_pwd_error());
	ft_putendl_fd(buf, STDOUT_FILENO);
	my_free(buf);
	return (SUCCESS_EXIT_CODE);
}
