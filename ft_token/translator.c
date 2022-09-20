/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 00:53:33 by minsuki2         ###   ########.fr       */
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


#include "../ft_string/ft_string.h"

void	quote_translator(t_lx_token *cur_token, char **cur_token_str)
{
	(*cur_token_str)++;

	ft_chrjoin_myself(&cur_token_str->interpreted_str, **cur_token_str);
	return (TRUE);
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

int dollar_translator(t_lx_token *cur_token, char **cur_token_str, \
															int split_flag)
{
	char	*find_pos;
	char	*chunk;

	find_pos = _get_pos_dollar_chunk(*cur_token_str);
	chunk = ft_strcpy(*cur_token_str, find_pos);
	*cur_token_str = find_pos;
	chunk = _make_dollar_interpreted(chunk);
	if (!chunk)
		return (FALSE);
	cursor_to_space(split_flag, chunk);
	ft_strjoin_self_add_free(&cur_token->interpreted_str, \
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
	if ()
	str_cur = cursor_to_space(split_flag, find_str);
	while ()
	*cur_token_str =

	return ()

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

void	wildcard_translator(t_lx_token **cur_token, char **cur_token_str)
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
	char_dimen2_free(splited);
}
