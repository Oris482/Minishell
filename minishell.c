/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/14 21:23:06 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;


	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	print_token_list(token_list);	// debug
	print_token_next(token_list);	// debug
	print_token_prev(token_list);	// debug
	root_tree = parser(token_list);
	if (!root_tree)
		return ;
	printf("----------- < TREE > --------------\n\n");
	print_ascii_tree(root_tree);	// debug
	executor(root_tree, TRUE);
	list_tree_free(NULL, root_tree);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;
	char			**strs; // debug

	signal_handler();
	terminal_off_control_chars();
	set_exit_status(0);
	envp_to_dict(envp);

	printf("\nreal_total = %d\n", print_strs(envp));
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	strs = dict_to_envp();
	printf("\nmy_total = %d\n", print_strs(strs));
	char_dimen2_free(strs);
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
		// list_tree_free(t_dict);
		system("leaks -q minishell");
	}
	(void)argc;
	(void)argv;
	return (0);
}
