/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_target_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:28 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

static int	_count_compressed_len(char *target_str, const char target)
{
	int	len;

	len = 0;
	while (*target_str)
	{
		len++;
		while (*target_str && is_target_char(*target_str, target) \
				&& is_target_char(*(target_str + 1), target))
			target_str++;
		target_str++;
	}
	return (len);
}

char	*compress_target_char(char *target_str, const char target)
{
	int		idx;
	char	*compressed_str;

	compressed_str = \
			(char *)malloc(_count_compressed_len(target_str, target) + 1);
	idx = 0;
	while (*target_str)
	{
		compressed_str[idx++] = *target_str;
		while (*target_str && is_target_char(*target_str, target) \
				&& is_target_char(*(target_str + 1), target))
			target_str++;
		target_str++;
	}
	compressed_str[idx] = '\0';
	return (compressed_str);
}
