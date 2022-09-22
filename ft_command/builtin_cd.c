/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:57:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 22:06:30 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_alloc.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_token.h"

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

int	set_oldpwd_then_chdir(t_dict dict[], const char *dst_path)
{
	char	*cwd;
	int		chdir_status;

	cwd = getcwd(NULL, 1);
	if (dst_path && *dst_path != '/' && cwd == NULL)
		return (print_error_str("cd", NULL, \
				"Invalid current working directory", GENERAL_EXIT_CODE));
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
			put_dict(dict, ft_strdup("OLDPWD"), cwd);
		else
			erase_dict(dict, "OLDPWD");
		put_dict(dict, ft_strdup("PWD"), getcwd(NULL, 1));
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

int	builtin_cd(t_dict dict[], t_lx_token *token)
{
	t_lx_token			*arg_token;
	char				*path;

	arg_token = token;
	if (builtin_option_arg_checker(&arg_token) == OPTION_ERROR)
		return (print_error_str("cd", get_token_str(arg_token), \
				"invalid option", INVALID_OPTION_EXIT_CODE));
	if (arg_token == NULL || (arg_token->interpret_symbol & DOLLAR \
									&& get_token_str(arg_token) == NULL))
	{
		path = my_getenv(dict, "HOME");
		if (path == NULL)
			return (print_error_str("cd", NULL, \
					"HOME not set", GENERAL_EXIT_CODE));
	}
	else if ((get_token_str(arg_token) == NULL \
				|| ft_strlen(get_token_str(arg_token)) == 0) \
				&& arg_token->interpret_symbol & DQUOTE)
		path = NULL;
	else if (ft_strcmp("-", get_token_str(arg_token)))
		path = my_getenv(dict, "OLDPWD");
	else
		path = get_token_str(arg_token);
	return (set_oldpwd_then_chdir(dict, path));
}
