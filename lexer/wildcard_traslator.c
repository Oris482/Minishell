/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_traslator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:03:18 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/29 12:53:47 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "myfunc.h"

int	ft_strcnt(const char *s, const char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			cnt++;
		s++;
	}
	return (cnt);
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	char	*start;

	ret = (char *)malloc(sizeof(char) * \
			(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (ret == NULL)
		exit(GENERAL_EXIT_CODE);
	start = ret;
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	while (*s3)
		*ret++ = *s3++;
	*ret = '\0';
	return (start);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	*start;
	char	*end;
	int		idx;

	ret = (char **)malloc(sizeof(char *) * (ft_strcnt(s, c) + 2));
	if (ret == NULL)
		exit(GENERAL_EXIT_CODE);
	idx = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		end = (char *)s;
		ret[idx++] = ft_strcpy(start, end + 1);
	}
	ret[idx] = NULL;
	return (ret);
}

t_lx_token	*_make_token(char *str, int type)
{
	t_lx_token	*ret;

	ret = (t_lx_token *)malloc(sizeof(t_lx_token));
	if (ret == NULL)
		exit(GENERAL_EXIT_CODE);
	ret->token_str = NULL;
	ret->interpreted_str = str;
	ret->token_type = type;
	ret->next = NULL;
	return (ret);
}

void	_files_to_node(t_lx_token **cur, t_file *files, \
						char *match_target, char *pwd)
{
	char		*temp;
	int			idx;

	idx = 0;
	while (idx < files->n)
	{
		if (files[idx].match_flag)
		{
			if (!((*cur)->pass_flag))
			{
				temp = (*cur)->interpreted_str;
				(*cur)->interpreted_str = ft_strjoin(pwd, "/", files[idx].name);
				(*cur)->pass_flag = 1;
				free(temp);
			}
			else
			{
				(*cur)->next = _make_token(ft_strjoin(pwd, \
											"/", files[idx].name), WORD);
				(*cur) = (*cur)->next;
			}
		}
		idx++;
	}
}

int	get_target_level(char **splited)
{
	int	idx;

	idx = 0;
	while (splited[idx])
		idx++;
	return (idx - 1);
}

void	recursive_find_files(t_lx_token **cur, int cur_level, \
							char *pwd, char **splited)
{
	const int	dir_flag = ft_strcnt(splited[cur_level], '/');
	const int	target_level = get_target_level(splited);
	t_file		*files;
	int			idx;
	int			matching_cnt;


	files = get_files_cur_pwd(pwd, dir_flag);
	matching_cnt = is_matching_file(splited[cur_level], files);
	idx = 0;
	if (cur_level == target_level && matching_cnt > 0)
		_files_to_node(cur, files, splited[cur_level], pwd);
	else
	{
		while (files && idx < files->n)
		{
			if (files[idx].match_flag)
				recursive_find_files(cur, cur_level + 1, \
								ft_strjoin(pwd, "/", files[idx].name), splited);
			idx++;
		}
	}
	free(pwd);
	my_closedir(files->dirp);
	free(files);
}

void	wildcard_translator(t_lx_token **cur)
{
	char	*compressed_str;
	char	*temp;
	char	**splited;
	int		target_level;
	char	*pwd;

	compressed_str = compress_target_char((*cur)->interpreted_str, '*');
	temp = compressed_str;
	compressed_str = compress_target_char(temp, '/');
	free(temp);
	target_level = ft_strcnt(compressed_str, '/');
	splited = ft_split(compressed_str, '/');
	free(compressed_str);
	pwd = getcwd(NULL, 0);
	recursive_find_files(cur, 0, pwd, splited);
	free(splited);
}