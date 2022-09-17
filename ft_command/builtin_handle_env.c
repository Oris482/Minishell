/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handle_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:08:01 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 23:29:33 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_string.h"
#include "ft_environ.h"
#include "ft_alloc.h"

int	builtin_env(t_lx_token *token)
{
	int		idx;
	t_dict	*cur;

	if (token->next)
		return (GENERAL_EXIT_CODE);
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

static int _get_env_nameval_at_token(t_lx_token *token, \
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
	if (check_vaild_env_name(*name) == FALSE)
		return (FALSE);
	if (value && *pos)
		*value = ft_strdup(pos + 1);
	return (TRUE);
}

int	builtin_unset(t_lx_token *token)
{
	char	*name;
	int		rtn_exit_code;

	if (!token->next)
		return (SUCCESS_EXIT_CODE);
	rtn_exit_code = SUCCESS_EXIT_CODE;
	while (token->next)
	{
		token = token->next;
		if (_get_env_nameval_at_token(token, &name, NULL) == FALSE)
		{
			rtn_exit_code = print_error_str("unset", name, \
								"not a valid identifier", GENERAL_EXIT_CODE);
			continue ;
		}
		erase_dict(name);
	}
	return (rtn_exit_code);
}

static int _put_export_msg(void)
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
	char	*name;
	char	*value;
	int		rtn_exit_code;

	if (!token->next)
		return (_put_export_msg());
	rtn_exit_code = SUCCESS_EXIT_CODE;
	while (token->next)
	{
		token = token->next;
		if (_get_env_nameval_at_token(token, &name, &value) == FALSE)
		{
			rtn_exit_code = print_error_str("export", name, \
								"not a valid identifier", GENERAL_EXIT_CODE);
			my_multi_free(name, value, NULL, NULL);
			continue ;
		}
		put_dict(name, value);
	}
	return (rtn_exit_code);
}
