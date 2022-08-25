/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/25 11:06:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer/lexer.h"
#include "liner/liner.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_lx_token		*token_list;

	signal_handler();
	terminal_off_control_chars();
	while (true)
	{
		token_list = NULL;
		full_line = line_handler();
		if (strcmp(full_line, "") != 0)
			add_history(full_line);
		if (lexer(&token_list, full_line, envp) == ERROR)
			return (1);
		free(full_line);
		print_token_list(token_list);
		free(token_list);
	}
	return (0);
}
