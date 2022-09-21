/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:40:10 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 17:04:15 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_check.h"
#include "ft_token.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_file.h"
#include "ft_environ.h"

char	*cursor_to_space(int split_flag, char *str_cur)
{
	while (*str_cur)
	{
		if (split_flag && ft_isspace(*str_cur))
			return (str_cur);
		str_cur++;
	}
	return (str_cur);
}


