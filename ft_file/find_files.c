/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:35:33 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 19:10:16 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_file.h"
#include "ft_string.h"
#include "ft_token.h"
#include "ft_alloc.h"

static int	_check_match_files(char *input, char *name)
{
	if (*input != '.' && *name == '.')
		return (FALSE);
	while (*input || *name)
	{
		if (*input == '*' && ((*name && (*(input + 1) == '\0' \
			|| *(input + 1) == '/' || *(input + 1) != *name) && name++) \
			|| ((*(input + 1) == '/' || *(input + 1) == *name) && input++)))
			continue ;
		if (*input == '/' && input++)
			continue ;
		if (*input == *name && input++ && name++)
			continue ;
		return (FALSE);
	}
	return (TRUE);
}

int	is_matching_file(char *input, t_file *const files)
{
	int			i;
	int			cnt;
	char		*wildcard_flag;

	i = 0;
	cnt = 0;
	wildcard_flag = ft_strchr(input, '*');
	while (i < files->n)
	{
		files[i].match_flag = _check_match_files(input, files[i].name);
		if (files[i].match_flag && ++cnt)
			if (!wildcard_flag)
				return (cnt);
		i++;
	}
	return (cnt);
}

static t_lx_token	*_make_wildcard_token(char *str)
{
	t_lx_token	*ret;

	ret = make_token_node(NULL, WORD);
	ret->interpret_symbol = WILDCARD;
	ret->interpreted_str = str;
	return (ret);
}

static void	_files_to_node(t_lx_token **cur, t_file *files, \
						char *pwd, int dir_flag)
{
	char		*temp;
	int			idx;

	idx = 0;
	while (idx < files->n)
	{
		if (!files[idx].match_flag && ++idx)
			continue ;
		if (!((*cur)->pass_flag))
		{
			temp = (*cur)->interpreted_str;
			(*cur)->interpreted_str = path_plus_filename(pwd, files, \
														idx, dir_flag);
			free(temp);
		}
		else
		{
			(*cur)->next = _make_wildcard_token(path_plus_filename(pwd, \
													files, idx, dir_flag));
			(*cur) = (*cur)->next;
		}
		(*cur)->pass_flag = 1;
		idx++;
	}
}

void	recursive_find_files(t_lx_token **cur, int cur_level, \
							char *pwd, char **splited)
{
	const char	dir_flag = !!ft_strchr(splited[cur_level], '/');
	const int	target_level = get_target_level(splited);
	t_file		*files;
	int			idx;
	int			matching_cnt;

	files = get_files_cur_pwd(pwd, dir_flag);
	if (!files)
		return ;
	matching_cnt = is_matching_file(splited[cur_level], files);
	idx = -1;
	if (cur_level == target_level && matching_cnt > 0)
		_files_to_node(cur, files, pwd, dir_flag);
	else
	{
		while (++idx < files->n)
			if (files[idx].match_flag)
				recursive_find_files(cur, cur_level + 1, \
							ft_strsjoin(pwd, files[idx].name, "/"), splited);
	}
	files_free(files);
	my_multi_free(pwd, NULL, NULL, NULL);
}
