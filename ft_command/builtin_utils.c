/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:18:27 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 22:13:04 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_token.h"
#include "ft_string.h"

static void	_option_arg_counter(t_lx_token *token, \
												int *option_cnt, int *arg_cnt)
{
	char		*token_str;

	while (token)
	{
		token_str = get_token_str(token);
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
