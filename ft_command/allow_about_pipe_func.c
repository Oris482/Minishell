/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allow_about_pipe_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:37:35 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 20:47:30 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_print.h"
#include <unistd.h>
#include <stdlib.h>

int	my_dup(int fildes)
{
	int	ret;

	ret = dup(fildes);
	if (ret == ERROR)
		exit(print_error_str("dup", NULL, NULL, GENERAL_EXIT_CODE));
	return (ret);
}

int	my_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret == ERROR)
		exit(print_error_str("dup2", NULL, NULL, GENERAL_EXIT_CODE));
	return (ret);
}

int	my_pipe(int files[2])
{
	int	ret;

	ret = pipe(files);
	if (ret == ERROR)
		exit(print_error_str("pipe", NULL, NULL, GENERAL_EXIT_CODE));
	return (ret);
}

pid_t	my_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		exit(print_error_str("fork", NULL, NULL, GENERAL_EXIT_CODE));
	return (pid);
}
