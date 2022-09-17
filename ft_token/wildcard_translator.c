/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_translator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:03:18 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 22:53:18 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_file.h"

static int	_level_check(const char *s)
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

static char	**_path_split(char *start)
{
	char	*cursor;
	char	*end;
	char	**ret;
	int		idx;

	cursor = ft_strchr(start, '*');
	ret = (char **)my_malloc(sizeof(char *) * (_level_check(cursor) + 2));
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

void	wildcard_translator(t_lx_token **cur)
{
	char	*compressed_str;
	char	*temp;
	char	**splited;
	char	*pwd;

	pwd = NULL;
	compressed_str = compress_target_char((*cur)->interpreted_str, '*');
	temp = compressed_str;
	compressed_str = compress_target_char(compressed_str, '/');
	my_free(temp);
	splited = _path_split(compressed_str);
	my_free(compressed_str);
	ft_strjoin_self(&pwd, splited[0]);
	recursive_find_files(cur, 1, pwd, splited);
	my_free(splited);
}
