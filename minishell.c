/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 23:55:34 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_debug/ft_debug.h"
#include "ft_alloc.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_library.h"

static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;

	token_list = lexer(full_line, oflag);
	if (!token_list)
		return ;
	root_tree = parser(token_list);
	if (!root_tree)
		return ;
	executor(root_tree, TRUE);
	list_tree_free(NULL, root_tree);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	char			*cur_shlvl;
	t_oflag			oflag;

	set_init_signal();
	terminal_off_control_chars();
	set_exit_status(0);
	envp_to_dict(envp);
	put_dict(ft_strdup("OLDPWD"), NULL);
	erase_dict("_");
	cur_shlvl = my_getenv("SHLVL");
	if (cur_shlvl == NULL)
		put_dict(ft_strdup("SHLVL"), ft_strdup("1"));
	else
		put_dict(ft_strdup("SHLVL"), ft_itoa(ft_atoi(cur_shlvl) + 1));
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
