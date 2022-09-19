/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 20:59:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_file.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_environ.h"

static char	*_make_dollar_find_str(char *chunk)
{
	char	*ret_str;

	if (*chunk == '?')
	{
		ret_str = ft_itoa(get_exit_status());
		ft_strjoin_self(&ret_str, chunk + 1);
	}
	else if (*chunk == '$' || *chunk == '\0')
		ret_str = ft_chr_to_str('$');
	else
		ret_str = my_getenv(chunk);
	if (!ret_str || !*ret_str)
		return (NULL);
	return (ret_str);
}

void	dollar_translator(t_lx_token *token_cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	find_str = _make_dollar_find_str(chunk);
	if (!find_str)
		return ;
	str_cur = cursor_to_space(split_flag, find_str);
	ft_strjoin_self_add_free(&token_cur->interpreted_str, \
												ft_strcpy(find_str, str_cur));
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		if (token_cur->interpret_symbol & WILDCARD)
			wildcard_translator(&token_cur);
		find_str = str_cur;
		str_cur = cursor_to_space(split_flag, find_str);
		token_cur->next = make_token_node(NULL, WORD);
		token_cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		token_cur->next->interpret_symbol |= DOLLAR * split_flag \
			| WILDCARD * !!ft_strchr(token_cur->next->interpreted_str, '*');
		token_cur = token_cur->next;
	}
}

void	dquote_translator(t_lx_token *cur, char *chunk)
{
	char	*pos;
	char	*tmp;

	while (*chunk)
	{
		pos = ft_strchr_null(chunk, '$');
		ft_strjoin_self_add_free(&cur->interpreted_str, \
													ft_strcpy(chunk, pos));
		chunk = pos;
		if (*chunk == '$' && pos++)
		{
			while (*pos)
			{
				if (is_token_seperator(*pos) || is_interpret_symbol(*pos) \
							|| (!is_env_chr(*pos, IDX_ONE_OR_MORE) \
												&& !is_question_mark(*pos)))
					break ;
				pos++;
			}
			tmp = ft_strcpy(chunk + 1, pos);
			dollar_translator(cur, tmp, 0);
			my_free(tmp);
			chunk = pos;
		}
	}
}

void	tilde_translator(t_lx_token *cur, char *chunk)
{
	char	*env_home;

	env_home = NULL;
	if (is_tilde(*(cur->token_str)) && !cur->interpreted_str \
		&& (*(chunk + 1) == '\0' || *(chunk + 1) == '/'))
		env_home = my_getenv("HOME");
	if (env_home != NULL)
		chunk++;
	ft_strjoin_self(&cur->interpreted_str, env_home);
	ft_strjoin_self(&cur->interpreted_str, chunk);
	return ;
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
	splited = path_split(compressed_str);
	my_free(compressed_str);
	ft_strjoin_self(&pwd, splited[0]);
	recursive_find_files(cur, 1, pwd, splited);
	my_free(splited);
}
