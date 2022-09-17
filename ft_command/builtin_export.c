/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:08:15 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

int put_export_msg(void)
{
	int		idx;
	t_dict	*cur;

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

int get_env_nameval_at_token(t_lx_token *token, char **name, char **value)
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

int	builtin_export(t_lx_token *token)
{
	int		idx;
	char	*name;
	char	*value;
	int		rtn_exit_code;

	if (!token->next)
		return (put_export_msg());
	rtn_exit_code = SUCCESS_EXIT_CODE;
	while (token->next)
	{
		token = token->next;
		if (get_env_nameval_at_token(token, &name, &value) == FALSE)
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
