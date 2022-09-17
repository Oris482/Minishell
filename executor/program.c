/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:59:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 13:30:14 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include "../minishell.h"

char	*find_cmd_path(char *cmd)
{
	const char	*set_path = my_getenv("PATH");
	char		*find_path;
	t_file		*files;
	char		*pos;

	find_path = NULL;
	while (set_path)
	{
		pos = ft_strchr_null(set_path, ':');
		find_path = ft_strcpy(set_path, pos);
		files = get_files_cur_pwd(find_path, 0);
		if (files && is_matching_file(cmd, files) > 0)
			break ;
		// while (files->n)
		//     my_free(files->name);
		// my_multi_free(find_path, files, NULL, NULL);
		my_multi_free(find_path, NULL, NULL, NULL);
		set_path = pos + (*pos != '\0');
	}
	if (!find_path || !set_path)
		return (NULL);
	return (ft_strjoin_self(&find_path, "/"));
}

int	count_cur_token(t_lx_token *token)
{
	int	cnt;

	cnt = 0;
	while (token && ++cnt)
		token = token->next;
	return (cnt);
}

char **make_cmd_argv(char *cmd_str, t_lx_token *token)
{
	int		i;
	char	**cmd_argv;
	int		cnt;

	cnt = count_cur_token(token);
	cmd_argv = (char **)my_calloc(cnt + 1, sizeof(char *));
	i = 0;
	cmd_argv[i] = ft_strdup(cmd_str);
	while (++i < cnt)
	{
		token = token->next;
		cmd_argv[i] = ft_strdup(token->interpreted_str);
		if (cmd_argv[i])
			cmd_argv[i] = ft_strdup(token->token_str);
	}
	cmd_argv[cnt] = NULL;
	return (cmd_argv);
}

int	failed_execve(char *cmd_str, char *cmd_path, char **cmd_argv, char **cmd_envp)
{
	int			rtn_exit_code;

	errno = 2;
	rtn_exit_code = print_error_str(cmd_str, NULL, NULL, 127);
	my_free(cmd_path);
	char_dimen2_free(cmd_argv);
	char_dimen2_free(cmd_envp);
	exit(rtn_exit_code);
}

void	execute_middleware(t_lx_token *token)
{
	char		*cmd_str;
	char		*cmd_path;
	char		**cmd_argv;
	char		**cmd_envp;

	cmd_str = token->interpreted_str;
	if (!cmd_str)
		cmd_str = token->token_str;
	cmd_path = cmd_str;
	if (ft_strchr(cmd_str, '/') == NULL)
	{
		cmd_path = find_cmd_path(cmd_str);
		if (!cmd_path)
			exit(print_error_str(cmd_str, NULL, "command not found", 127));
		ft_strjoin_self(&cmd_path, cmd_str);
	}
	else
		cmd_str = ft_strrchr_right_away(ft_strchr_null(cmd_str, '\0'), '/', cmd_str) + 1;
	cmd_argv = make_cmd_argv(cmd_str, token);
	cmd_envp = dict_to_envp();
	execve(cmd_path, cmd_argv, cmd_envp);
	failed_execve(cmd_str, cmd_path, cmd_argv, cmd_envp);
}
