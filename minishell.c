/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/07 02:42:48 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

static void	_minishell_routine(char *full_line, char *envp[])
{
	t_lx_token		*token_list;

	token_list = NULL;
	lexer(&token_list, full_line, envp);
	print_token_list(token_list);
	print_token_next(token_list);
	print_token_prev(token_list);
	if (check_syntax_error(token_list) == SUCCESS)
		parser(token_list);
	my_multi_free(full_line, token_list, NULL, NULL);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	while (true)
	{
		full_line = line_handler(&oflag);
		if (full_line && *full_line != '\0')
			add_history(full_line);
		if (!oflag.quote && !oflag.parentheses)
			_minishell_routine(full_line, envp);
	}
	(void)argc;
	(void)argv;
	return (0);
}
