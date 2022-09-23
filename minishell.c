/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/23 17:18:13 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_alloc.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_library.h"
#include "ft_print.h"
#include "ft_tree.h"

void	handle_shlvl_env(t_dict dict[])
{
	char	*cur_shlvl;

	add_dict(dict, ft_strdup("OLDPWD"), NULL, NULL);
	cur_shlvl = my_getenv(dict, "SHLVL");
	if (cur_shlvl == NULL)
		put_dict(dict, ft_strdup("SHLVL"), ft_strdup("1"));
	else
		put_dict(dict, ft_strdup("SHLVL"), ft_itoa(ft_atoi(cur_shlvl) + 1));
}

static void	_minishell_init_setting(t_dict dict[], char *envp[])
{
	int		fd;
	char	line[2045];

	set_init_signal();
	terminal_off_control_chars();
	set_exit_status(0);
	envp_to_dict(dict, envp);
	erase_dict(dict, "_");
	erase_dict(dict, "OLDPWD");
	handle_shlvl_env(dict);
	fd = open("ascii_art", O_RDONLY);
	if (fd > 0 && read(fd, line, 2045) > 0)
		ft_putstr_fd(line, STDOUT_FILENO);
	close(fd);
}

static void	_minishell_routine(t_dict dict[], char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;

	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	root_tree = parser(dict, token_list);
	if (!root_tree)
		return ;
	terminal_on_control_chars();
	executor(dict, root_tree, TRUE);
	terminal_off_control_chars();
	list_tree_free(NULL, root_tree);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;
	t_dict			dict[53];

	_minishell_init_setting(dict, envp);
	while (TRUE)
	{
		full_line = liner(&oflag);
		if (full_line && *full_line == '\0')
		{
			my_multi_free(full_line, NULL, NULL, NULL);
			continue ;
		}
		add_history(full_line);
		_minishell_routine(dict, full_line, &oflag);
		my_multi_free(full_line, NULL, NULL, NULL);
	}
	(void)argc;
	(void)argv;
	return (0);
}
