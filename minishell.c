/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 00:26:08 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_debug/ft_debug.h"
#include "ft_alloc.h"
#include "ft_environ.h"

static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;


	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	// print_token_next(token_list);
	root_tree = parser(token_list);
	if (!root_tree)
		return ;
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
	envp_to_dict(envp);
	while (TRUE)
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
		// system("leaks -q minishell");
	}
	(void)argc;
	(void)argv;
	return (0);
}
