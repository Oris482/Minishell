/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handle_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:08:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/18 22:27:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_string.h"
#include "ft_environ.h"
#include "ft_alloc.h"
#include "ft_token.h"

int	builtin_env(t_lx_token *token)
{
	int			idx;
	int			err_code;
	t_lx_token	*arg_token;
	t_dict		*cur;

	arg_token = token;
	err_code = builtin_option_arg_checker(&arg_token);
	if (err_code == OPTION_ERROR)
		return (print_error_str("env", get_token_str(arg_token), \
								"invalid option", INVALID_OPTION_EXIT_CODE));
	else if (err_code == ARG_ERROR)
		return (print_error_str("env", get_token_str(arg_token), \
								"invalid arg", GENERAL_EXIT_CODE));
	idx = 0;
	while (idx < DICT_MAX)
	{
		cur = &g_dict[idx];
		while (cur->next)
		{
			cur = cur->next;
			if (!cur->value)
				continue ;
			ft_putstr_fd(cur->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(cur->value, STDOUT_FILENO);
		}
		idx++;
	}
	return (SUCCESS_EXIT_CODE);
}

static int	_get_env_nameval_at_token(t_lx_token *token, \
										char **name, char **value)
{
	char	*merge_str;
	char	*pos;

	if (!token || !name)
		return (FALSE);
	merge_str = token->interpreted_str;
	if (!token->interpreted_str)
		merge_str = token->token_str;
	if (value)
	{
		*value = NULL;
		pos = ft_strchr_null(merge_str + 1, '=');
		*name = ft_strcpy(merge_str, pos);
	}
	else
		*name = merge_str;
	if (check_valid_env_name(*name) == FALSE)
		return (FALSE);
	if (value && *pos)
		*value = ft_strdup(pos + 1);
	return (TRUE);
}

int	builtin_unset(t_lx_token *token)
{
	t_lx_token	*arg_token;
	char		*name;
	int			rtn_exit_code;

	arg_token = token;
	if (builtin_option_arg_checker(&arg_token) == OPTION_ERROR)
		return (print_error_str("unset", get_token_str(arg_token), \
								"invalid option", INVALID_OPTION_EXIT_CODE));
	rtn_exit_code = SUCCESS_EXIT_CODE;
	while (arg_token)
	{
		if (_get_env_nameval_at_token(arg_token, &name, NULL) == TRUE)
			erase_dict(name);
		else
			rtn_exit_code = print_error_str("unset", name, \
								"not a valid identifier", GENERAL_EXIT_CODE);
		arg_token = arg_token->next;
	}
	return (rtn_exit_code);
}

static int	_put_export_msg(void)
{
	int		idx;
	t_dict	*cur;

	idx = 0;
	while (idx < DICT_MAX)
	{
		cur = &g_dict[idx];
		while (cur->next)
		{
			cur = cur->next;
			ft_putstr_fd(EXPORT_HEAD_MSG, STDOUT_FILENO);
			ft_putstr_fd(cur->name, STDOUT_FILENO);
			if (cur->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(cur->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		idx++;
	}
	return (SUCCESS_EXIT_CODE);
}

int	builtin_export(t_lx_token *token)
{
	t_lx_token	*arg_token;
	char		*name;
	char		*value;
	int			rtn_exit_code;

	arg_token = token;
	if (builtin_option_arg_checker(&arg_token) == OPTION_ERROR)
		return (print_error_str("export", get_token_str(arg_token), \
								"invalid option", INVALID_OPTION_EXIT_CODE));
	if (!arg_token)
		return (_put_export_msg());
	rtn_exit_code = SUCCESS_EXIT_CODE;
	while (arg_token)
	{
		if (_get_env_nameval_at_token(arg_token, &name, &value) == TRUE)
			put_dict(name, value);
		else
		{
			rtn_exit_code = print_error_str("export", name, \
								"not a valid identifier", GENERAL_EXIT_CODE);
			my_multi_free(name, value, NULL, NULL);
		}
		arg_token = arg_token->next;
	}
	return (rtn_exit_code);
}
