/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:52:19 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/12 02:44:35 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myfunc.h"
#include "minishell.h"

char	*my_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		ft_putendl_fd("BYE", STDOUT_FILENO);
		exit(0);
	}
	return (line);
}
