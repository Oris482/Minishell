/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:57:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 00:38:33 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*_get_path(t_lx_token *token)
{
	if (token == NULL || get_token_str(token) == NULL)
		return (NULL); // 환경변수 HOME
	return (get_token_str(token));
}

static int	_handle_cd_error(char *path, char free_flag)
{
	int		exit_code;
	char	*err_msg;

	if (errno != UNDEFINED)
	{
		exit_code = GENERAL_EXIT_CODE;
		if (errno == EACCES)
		{
			exit_code = PERMISSION_EXIT_CODE;
			err_msg = "Permission denied";
		}
		else if (errno == ENOENT)
			err_msg = "No such file or directory";
		else if (errno == ENOTDIR)
			err_msg = "Not a directory";
		else
			print_error_str("cd", path, NULL, exit_code);
		print_error_str("cd", path, err_msg, exit_code);
		if (free_flag)
			my_free(path);
	}
	return (FALSE);
}

int	builtin_cd(t_lx_token *token)
{
	char	*path;
	int		free_flag;

	path = NULL;
	free_flag = 0;
	if (token->next && get_token_str(token->next) != NULL && \
						ft_strlen(get_token_str(token->next)) == 0)
	{
		path = getcwd(path, 1);
		if (path == NULL)
			return (print_error_str("cd", NULL, NULL, GENERAL_EXIT_CODE));
		free_flag = 1;
	}
	else
		path = _get_path(token->next);
	if (chdir(path) == ERROR)
		return (_handle_cd_error(path, free_flag));
	if (free_flag)
		my_free(path);
	return (SUCCESS_EXIT_CODE);
}
