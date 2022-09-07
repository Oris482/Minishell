/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 03:46:14 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

//t_info env

static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;


	if (lexer(&token_list, full_line, oflag) == ERROR)
		return ;
	print_token_list(token_list);
	print_token_next(token_list);
	print_token_prev(token_list);
	if (parser(&root_tree, token_list) == ERROR)
		return ;
	printf("----------- < TREE > --------------\n\n");
	print_ascii_tree(root_tree);
	my_multi_free(full_line, token_list, NULL, NULL);
	// tree_traversal(root, TREE_ALL, free);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	//envp 할당
	while (true)
	{
		full_line = liner(&oflag);
		if (full_line && *full_line == '\0')
			continue ;
		add_history(full_line);
		if (!oflag.quote && !oflag.parentheses)
			_minishell_routine(full_line, &oflag);
	}
	(void)argc;
	(void)argv;

	return (0);
}
