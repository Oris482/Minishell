/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:59:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/25 14:50:09 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_command.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_token.h"
#include "ft_print.h"

static char	*_find_cmd_path(t_dict dict[], char *cmd)
{
	const char	*set_path = my_getenv(dict, "PATH");
	char		*find_path;
	char		*pos;
	struct stat	statbuf;

	if (!set_path)
		return (NULL);
	find_path = NULL;
	while (*set_path)
	{
		pos = ft_strchr_null(set_path, ':');
		find_path = ft_strcpy(set_path, pos);
		ft_strjoin_self(&find_path, "/");
		if (stat(ft_strjoin_self(&find_path, cmd), &statbuf) == 0)
			break ;
		my_multi_free(find_path, NULL, NULL, NULL);
		set_path = pos + (*pos != '\0');
	}
	if (!find_path || !*set_path)
		return (NULL);
	return (find_path);
}

static int	_count_cur_token(t_lx_token *token)
{
	int	cnt;

	cnt = 0;
	while (token && ++cnt)
		token = token->next;
	return (cnt);
}

char	**make_cmd_argv(char *cmd_str, t_lx_token *token)
{
	int		i;
	char	**cmd_argv;
	int		cnt;

	cnt = _count_cur_token(token);
	cmd_argv = (char **)my_calloc(cnt + 1, sizeof(char *));
	i = 0;
	cmd_argv[i] = ft_strdup(cmd_str);
	while (++i < cnt)
	{
		token = token->next;
		cmd_argv[i] = ft_strdup(get_token_str(token));
	}
	cmd_argv[cnt] = NULL;
	return (cmd_argv);
}

int	failed_execve(char *cmd_path, char **cmd_argv, char **cmd_envp)
{
	int			rtn_exit_code;

	if (errno == ENOTDIR || errno == EACCES)
		rtn_exit_code = print_error_str(cmd_path, NULL, NULL, 126);
	else if (errno == ENOENT)
		rtn_exit_code = print_error_str(cmd_path, NULL, NULL, 127);
	else if (errno == ENOEXEC)
		rtn_exit_code = print_error_str(cmd_path, NULL, NULL, 2);
	else
		rtn_exit_code = print_error_str(cmd_path, NULL, \
											NULL, GENERAL_EXIT_CODE);
	my_free(cmd_path);
	char_dimen2_free(cmd_argv);
	char_dimen2_free(cmd_envp);
	exit(rtn_exit_code);
}

void	execute_middleware(t_dict dict[], t_lx_token *token)
{
	char		*cmd_str;
	char		*cmd_path;
	char		**cmd_argv;
	char		**cmd_envp;
	struct stat	statbuf;

	cmd_str = get_token_str(token);
	cmd_path = cmd_str;
	if (ft_strchr(cmd_str, '/') == NULL)
	{
		cmd_path = _find_cmd_path(dict, cmd_str);
		if (!cmd_path)
			exit(print_error_str(cmd_str, NULL, "command not found", 127));
	}
	else
		cmd_str = ft_strrchr_right_away(ft_strchr_null(cmd_str, \
													'\0'), '/', cmd_str) + 1;
	stat(cmd_path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		exit(print_error_str(cmd_path, NULL, "is a directory", 126));
	cmd_argv = make_cmd_argv(cmd_str, token);
	cmd_envp = dict_to_envp(dict);
	execve(cmd_path, cmd_argv, cmd_envp);
	failed_execve(cmd_path, cmd_argv, cmd_envp);
}
