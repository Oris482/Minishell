/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:48:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 00:19:30 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
		return (print_error_str("pwd", NULL, NULL, GENERAL_EXIT_CODE));
	ft_putendl_fd(buf, STDOUT_FILENO);
	my_free(buf);
	return (SUCCESS_EXIT_CODE);
}
