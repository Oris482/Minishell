/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/20 11:38:54 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"

// unsigned char	find_interpret_symbol(char **token_str, \
//                                                 unsigned char target)
// {
//     if (target == UNDEFINED || target == DOLLAR)
//     {
//         while (**token_str && (!is_interpret_symbol(**token_str) \
//                             && is_env_chr(**token_str, IDX_ONE_OR_MORE)))
//             (*token_str)++;
//         return (is_interpret_symbol(**token_str));
//     }
//     else if (target == TILDE)
//     {
//         while (**token_str && !is_dollar(**token_str) \
//                             && !is_quote(**token_str))
//             (*token_str)++;
//         return (TILDE);
//     }
//     else
//     {
//         while ((is_quote(**token_str) | is_dollar(**token_str)) != target)
//             (*token_str)++;
//         return (target);
//     }
// }

static void	_make_chunk_middleware(char **str_startpoint, char **token_str, \
								char **str_chunk, unsigned char *symbol_type)
{
	*str_startpoint = *token_str;
	*symbol_type = UNDEFINED;
	if (is_interpret_symbol(**str_startpoint))
		*str_chunk = make_chunk_by_symbol(token_str, \
											*str_startpoint, symbol_type);
	else
	{
		find_interpret_symbol(token_str, TILDE);
		*str_chunk = ft_strcpy(*str_startpoint, *token_str);
	}
}


static void _get_pos_dollar_chunk(char *cur_token_str)
{
	int	i;

	i = -1;
	while (++i && (*cur_token_str)[i])
		if (!is_env_chr((*cur_token_str)[i], i))
			return (*cur_token_str + i);
	return (*cur_token_str + i);
}

static char	*_make_dollar_interpreted(char *chunk)
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
		ret_str = ft_strdup(my_getenv(chunk));
	if (!ret_str || !*ret_str)
		return (NULL);
	return (ret_str);
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
	while (*)
	{

	}
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


static int	_interpret_middleware(t_lx_token *cur_token, \
									unsigned char symbol_type, int split_flag)
{
	if (is_quote())
		return (quote_translator());
	else if (is_dquote())
		return (dquote_translator());
	else if (is_dollar())
		return (dollar_translator(cur_token, ));
	else if (c == '*')
		return (wildcard_translator());
	return (just_string());
}
// void	str_traversal(char **token_str, char interpret_chr, \
//                                                     void (*handler)(char **))
// {
//     if (token_str && **token_str == interpret_chr)
//         handler(token_str);
// }
void	interpreter(t_lx_token *token)
{
	char			*token_str;
	unsigned char	symbol_type;
	char			*str_startpoint;
	char			*str_chunk;

	token_str = token->token_str;
	while (*token_str)
	{
		split_flag = _interpret_middleware(token, symbol_type, split_flag);
		token_str++;
		token = token->next;
	}
}

