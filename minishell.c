/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 16:58:37 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;


	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	print_token_list(token_list);
	print_token_next(token_list);
	print_token_prev(token_list);
	root_tree = parser(token_list);
	if (!root_tree)
		return ;
	printf("----------- < TREE > --------------\n\n");
	print_ascii_tree(root_tree);
	executor(root_tree, TRUE);
	list_tree_free(NULL, root_tree);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	set_exit_status(0);
	(void)envp;
	// ft_str_array_dup envp 할당
	while (true)
	{
		full_line = liner(&oflag);
		// system("leaks -q minishell");
		if (full_line && *full_line == '\0')
		{
			my_multi_free(full_line, NULL, NULL, NULL);
			continue ;
		}
		add_history(full_line);
		_minishell_routine(full_line, &oflag);
		my_multi_free(full_line, NULL, NULL, NULL);
		// system("leaks -q minishell");
	}
	(void)argc;
	(void)argv;
	return (0);
}
