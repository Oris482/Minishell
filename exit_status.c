/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:34:06 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 00:33:05 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"

static int	*_get_address_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	set_exit_status(int status)
{
	int	*exit_status;

	exit_status = _get_address_exit_status();
	*exit_status = status;
	return ;
}

int	get_exit_status(void)
{
	int	*exit_status;

	exit_status = _get_address_exit_status();
	return (*exit_status);
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + SIG_DEFAULT_EXIT_CODE);
	else if (WIFSTOPPED(status))
		return (SIGSTOP + SIG_DEFAULT_EXIT_CODE);
	else if (WIFCONTINUED(status))
		return (SIGCONT + SIG_DEFAULT_EXIT_CODE);
	else
		return (GENERAL_EXIT_CODE);
}
