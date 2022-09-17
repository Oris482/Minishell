/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:09:31 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

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
		if (get_env_nameval_at_token(token, &name, NULL) == FALSE)
		{
			rtn_exit_code = print_error_str("unset", name, \
								"not a valid identifier", GENERAL_EXIT_CODE);
			continue ;
		}
		erase_dict(name);
	}
	return (rtn_exit_code);
}
