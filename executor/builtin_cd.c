/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:57:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/15 19:11:36 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	_handle_cd_error(const char *path)
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
			return (print_error_str("cd", path, NULL, exit_code));
		return (print_error_str("cd", path, err_msg, exit_code));
	}
	return (SUCCESS_EXIT_CODE);
}

int	set_oldpwd_then_chdir(const char *dst_path)
{
	char	*cwd;
	int		chdir_status;

	cwd = getcwd(NULL, 1);
	if (dst_path == NULL)
		dst_path = cwd;
	chdir_status = chdir(dst_path);
	if (chdir_status == ERROR)
	{
		my_free(cwd);
		return (_handle_cd_error(dst_path));
	}
	else
	{
		if (cwd != NULL)
			put_dict(ft_strdup("OLDPWD"), cwd);
		else
			erase_dict("OLDPWD");
		put_dict(ft_strdup("PWD"), getcwd(NULL, 1));
	}
	return (SUCCESS_EXIT_CODE);
}

char	*check_valid_cwd(char *path)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 1);
	if (cwd == NULL)
		return (NULL);
	my_free(cwd);
	return (path);
}

int	builtin_cd(t_lx_token *token)
{
	const t_lx_token	*arg_token = token->next;
	char				*path;

	if (arg_token == NULL || get_token_str(arg_token) == NULL)
		path = my_getenv("HOME");
	else if (ft_strlen(get_token_str(arg_token)) == 0)
		path = NULL;
	else if (ft_strcmp("-", get_token_str(arg_token)))
		path = my_getenv("OLDPWD");
	else
	{
		path = get_token_str(arg_token);
		if (*path != '/')
		{
			path = check_valid_cwd(path);
			if (path == NULL)
				return (print_error_str("cd", NULL, \
						"Invalid current working directory", \
							GENERAL_EXIT_CODE));
		}
	}
	return (set_oldpwd_then_chdir(path));
}
