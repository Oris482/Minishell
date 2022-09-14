/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/15 01:49:21 by minsuki2         ###   ########.fr       */
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
	put_dict(ft_strdup("ahh"), NULL);
	put_dict(ft_strdup("a"), ft_strdup(""));
	put_dict(ft_strdup("aB"), ft_strdup(""));
	put_dict(ft_strdup("a_"), ft_strdup(""));
	put_dict(ft_strdup("ab_"), ft_strdup(""));
	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	print_dictionary_lst();
	// printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	// strs = dict_to_envp();
	// printf("\nmy_total = %d\n", print_strs(strs));
	// char_dimen2_free(strs);
	// printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
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
