/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 22:14:56 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_alloc.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_library.h"

static void	_minishell_init_setting(char *envp[])
{
	char	*cur_shlvl;

	set_init_signal();
	terminal_off_control_chars();
	set_exit_status(0);
	envp_to_dict(envp);
	put_dict(ft_strdup("OLDPWD"), ft_strdup(""));
	erase_dict("_");
	cur_shlvl = my_getenv("SHLVL");
	if (cur_shlvl == NULL)
		put_dict(ft_strdup("SHLVL"), ft_strdup("1"));
	else
		put_dict(ft_strdup("SHLVL"), ft_itoa(ft_atoi(cur_shlvl) + 1));
}

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
	terminal_on_control_chars();
	executor(root_tree, TRUE);
	terminal_off_control_chars();
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
