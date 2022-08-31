/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_traslator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:03:18 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/31 19:56:55 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"
#include "myfunc.h"


test*
test*/

static int	_ft_strcnt_nullchr(const char *s, const char c)
{
	int	cnt;

	if (!s)
		return (FALSE);
	cnt = 0;
	if (*s == c)
		cnt++;
	while (*s && s++ && ++cnt)
		s = ft_strchr_null(s, c);
	return (cnt);
}

// int	level_check(const char *s)
// {
//     int		idx;
//     char	*old_slash;
//     int	wildcard_flag;
//
//     idx = 0;
//     wildcard_flag = 0;
//     old_slash = NULL;
//     s = ft_strchr(s, '*');
//     idx = ft_strcnt(s, '/');
//     // while (*s)
//     // {
//     //     s = ft_strchr(s, '*');
//     //     if (s)
//     //         idx++;
//     //     s = ft_strchr_null(s, '/');
//     //     if (old_slash != s)
//     //         idx++;						//처음에는 무조건 2증가
//     //     old_slash = s;
//     //     s += (*s == '/');
//     // }
//     return (idx);
// }

char	**path_split(char const *s)
{
	char	**ret;
	const char	*start = s;
	const char	*end;
	int		idx;
	int		wildcard_flag;

	start = *s;
	s = ft_strchr(s, '*');
	ret = (char **)my_malloc(sizeof(char *) * (ft_strcnt_null(s, '/') + 2));
	idx = 0;
	while (*s)
	{
		s = ft_strchr_null(s, '/');
		ret[idx++] = ft_strcpy(start, s + (*s));
		start = s + (!*s);

		// if (idx % 2 == 0)
		//     s = ft_strchr_null(s, '*');
		// else
		// end = s - (*s == '\0');
		// // end = ft_strrchr(s, )
		// while (*s && *end != '/')
		//     end--;
		// start = end;
		// s = ft_strchr_null(s, '/');
		// end  = s - (*s == '\0');
		// while (*s && end != '/')
		//     end--;
		// ret[idx++] = ft_strcpy(start, end++ + 1);
		// start = end;

		// wildcard_flag = FALSE;
		// while (*s == c)
		//     s++;
		// break ;
		// if (*start != '/')
		// start = (char *)s;
		// while ((*s && *s != c) || !wildcard_flag)
		// {
		//     if (*s == '*')
		//         wildcard_flag = TRUE;
		//     s++;
		// }
		// end = (char *)s;
		// ret[idx++] = ft_strcpy(start, end + 1);
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
				(*cur)->interpreted_str = ft_strsjoin(pwd, "/", files[idx].name);
				(*cur)->pass_flag = 1;
				free(temp);
			}
			else
			{
				(*cur)->next = _make_token(ft_strsjoin(pwd, \
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
	const int	dir_flag = _ft_strcnt(splited[cur_level], '/');
	const int	target_level = get_target_level(splited);
	t_file		*files;
	int			idx;
	int			matching_cnt;

	files = get_files_cur_pwd(pwd, dir_flag);
	if (!files)
		return ;
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
							ft_strsjoin(pwd, "/", files[idx].name), splited);
			idx++;
		}
	}
	my_closedir(files->dirp);
	my_multi_free(pwd, files, NULL, NULL);
}

void	wildcard_translator(t_lx_token **cur)
{
	char	*compressed_str;
	char	*temp;
	char	**splited;
	int		target_level;
	char	*pwd;

	pwd = NULL; 
	compressed_str = compress_target_char((*cur)->interpreted_str, '*');
	temp = compressed_str;
	compressed_str = compress_target_char(compressed_str, '/');
	free(temp);
	target_level = level_cnt(compressed_str);
	splited = path_split(compressed_str);
	free(compressed_str);
	ft_strjoin_self(&pwd, splited[0]);
	recursive_find_files(cur, 1, pwd, splited);
	free(splited);
}
