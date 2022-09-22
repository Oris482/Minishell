/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 17:14:22 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_alloc.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_library.h"
#include "ft_print.h"
#include "ft_debug/ft_debug.h"

static void	_minishell_init_setting(char *envp[])
{
	int		fd;
	char	line[2045];

	set_init_signal();
	terminal_off_control_chars();
	set_exit_status(0);
	envp_to_dict(envp);
	fd = open("ascii_art", O_RDONLY);
	if (fd > 0 && read(fd, line, 2045) > 0)
		ft_putstr_fd(line, STDOUT_FILENO);
	close(fd);
}

static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;

	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	print_token_list(token_list);
	print_token_next(token_list);
	root_tree = parser(token_list);
	if (!root_tree)
		return ;
	terminal_on_control_chars();
	executor(root_tree, TRUE);
	terminal_off_control_chars();
	print_ascii_tree(root_tree);
	list_tree_free(NULL, root_tree);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;

	_minishell_init_setting(envp);
	while (TRUE)
	{
		full_line = liner(&oflag);
		if (full_line && *full_line == '\0')
		{
			my_multi_free(full_line, NULL, NULL, NULL);
			continue ;
		}
		add_history(full_line);
		_minishell_routine(full_line, &oflag);
		my_multi_free(full_line, NULL, NULL, NULL);
	}
	(void)argc;
	(void)argv;
	return (0);
}
