/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/03 17:48:05 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

static void	_minishell_routine(t_lx_token *token_list)
{
	print_token_list(token_list);
	check_syntax_error(token_list);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_lx_token		*token_list;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	while (true)
	{
		token_list = NULL;
		full_line = line_handler(&oflag);
		if (full_line && *full_line != '\0')
			add_history(full_line);
		if (lexer(&token_list, full_line, envp) == ERROR)
			return (1);
		my_free(full_line);
		if (!oflag.quote && !oflag.parentheses)
			_minishell_routine(token_list);
		my_free(token_list);
	}
	(void)argc;
	(void)argv;
	return (0);
}
