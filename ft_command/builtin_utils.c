/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:18:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 21:26:43 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_token.h"
#include "ft_string.h"
#include "ft_print.h"

int	is_builtin(const char *str)
{
	if (ft_strcmp_ignore_capital("echo", str) == SUCCESS)
		return (BI_ECHO);
	else if (ft_strcmp_ignore_capital("cd", str) == SUCCESS)
		return (BI_CD);
	else if (ft_strcmp_ignore_capital("pwd", str) == SUCCESS)
		return (BI_PWD);
	else if (ft_strcmp_ignore_capital("export", str) == SUCCESS)
		return (BI_EXPORT);
	else if (ft_strcmp_ignore_capital("unset", str) == SUCCESS)
		return (BI_UNSET);
	else if (ft_strcmp_ignore_capital("env", str) == SUCCESS)
		return (BI_ENV);
	else if (ft_strcmp_ignore_capital("exit", str) == SUCCESS)
		return (BI_EXIT);
	else
		return (FALSE);
}

int	builtin_middleware(t_lx_token *token, int builtin_idx)
{
	if (builtin_idx == BI_ECHO)
		return (builtin_echo(token));
	else if (builtin_idx == BI_CD)
		return (builtin_cd(token));
	else if (builtin_idx == BI_PWD)
		return (builtin_pwd(token));
	else if (builtin_idx == BI_EXPORT)
		return (builtin_export(token));
	else if (builtin_idx == BI_UNSET)
		return (builtin_unset(token));
	else if (builtin_idx == BI_ENV)
		return (builtin_env(token));
	else if (builtin_idx == BI_EXIT)
		return (builtin_exit(token));
	return (ERROR);
}

static void	_option_arg_counter(t_lx_token *token, \
												int *option_cnt, int *arg_cnt)
{
	char		*token_str;

	while (token)
	{
		token_str = get_token_str(token);
		if (token_str == NULL)
			break ;
		if (*token_str != '-' || ft_strcmp("-", token_str))
			break ;
		if (ft_strcmp("--", token_str))
		{
			token = token->next;
			break ;
		}
		(*option_cnt)++;
		token = token->next;
	}
	while (token)
	{
		(*arg_cnt)++;
		token = token->next;
	}
}

static int	_builtin_set_to_target_token(t_lx_token **token)
{
	char	*token_str;

	(*token) = (*token)->next;
	if (*token)
	{
		token_str = get_token_str(*token);
		if (ft_strcmp("--", token_str))
			(*token) = (*token)->next;
	}
	return (SUCCESS);
}

int	builtin_option_arg_checker(t_lx_token **token)
{
	const char	*cmd = get_token_str(*token);
	int			option_cnt;
	int			arg_cnt;
	int			builtin_idx;

	option_cnt = 0;
	arg_cnt = 0;
	_option_arg_counter((*token)->next, &option_cnt, &arg_cnt);
	builtin_idx = is_builtin(cmd);
	if (option_cnt)
	{
		if (builtin_idx == BI_PWD || builtin_idx == BI_EXPORT \
			|| builtin_idx == BI_UNSET || builtin_idx == BI_ENV \
			|| builtin_idx == BI_CD)
		{
			(*token) = (*token)->next;
			return (OPTION_ERROR);
		}
	}
	if (arg_cnt && builtin_idx == BI_ENV)
	{
		_builtin_set_to_target_token(token);
		return (ARG_ERROR);
	}
	return (_builtin_set_to_target_token(token));
}
