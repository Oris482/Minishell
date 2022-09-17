/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:52:19 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/18 04:52:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_print.h"

char	*my_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		// ft_putendl_fd("BYE", STDOUT_FILENO);
		exit(get_exit_status());
	}
	return (line);
}
