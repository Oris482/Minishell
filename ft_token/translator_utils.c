/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:40:10 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 16:55:57 by jaesjeon         ###   ########.fr       */
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

static int	level_check(const char *s)
{
	int	cnt;

	cnt = 1;
	while (*s)
	{
		s++;
		s = ft_strchr_null(s, '/');
		if (*s == '/' && *(s + 1) != '\0')
			cnt++;
	}
	return (cnt);
}

char	**path_split(char *start)
{
	char	*cursor;
	char	*end;
	char	**ret;
	int		idx;

	cursor = ft_strchr(start, '*');
	ret = (char **)my_malloc(sizeof(char *) * (level_check(cursor) + 2));
	idx = 1;
	if (ft_strchr_null(start, '/') < cursor)
	{
		end = ft_strrchr_right_away(cursor, '/', start);
		ret[0] = ft_strcpy(start, ++end);
		start = end;
	}
	else
		ret[0] = (char *)my_calloc(2, sizeof(char));
	while (*cursor)
	{
		cursor = ft_strchr_null(cursor, '/');
		cursor += !!(*cursor);
		ret[idx++] = ft_strcpy(start, cursor);
		start = (char *)cursor;
	}
	ret[idx] = NULL;
	return (ret);
}

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
			(char *)my_malloc(_count_compressed_len(target_str, target) + 1);
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
