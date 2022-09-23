/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/23 17:05:50 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"


int	interpret_middleware(t_dict dict[], t_lx_token *cur_token, \
			char **cur_str, unsigned char symbol_type)
{
	int			ret;

	ret = ERROR;
	if (symbol_type == QUOTE)
		ret = quote_translator(cur_token, cur_str);
	else if (symbol_type == DOLLAR || symbol_type == (DOLLAR | DQUOTE))
		ret = dollar_translator(dict, cur_token, cur_str, symbol_type);
	else if (symbol_type == DQUOTE)
		ret = dquote_translator(dict, cur_token, cur_str);
	else if (symbol_type == WILDCARD)
		cur_token->interpret_symbol |= WILDCARD;
	else if (symbol_type == TILDE)
		ret = tilde_translator(dict, cur_token, cur_str);
	if (ret != ERROR)
		return (ret);
	ft_chrjoin_myself(&cur_token->interpreted_str, **cur_str, BACK);
	(*cur_str)++;
	return (NOT_SPERATE);
}
/* *line 26
 * 달러 다음 큰 따옴표 순으로 if 문을 작성해야 함
 * ㄴ DOLLAR를 만나서 DQUOTE에 들어갈 수 는 없지만
 * ㄴ DQUOTE를 만나서 DOLLAR에 들어갈 수 있음
 */

void	interpret_wildcard_token(t_lx_token **token)
{
	t_lx_token	*second_backup;

	while (*token)
	{
		if ((*token)->interpret_symbol & WILDCARD)
		{
			second_backup = (*token)->next;
			wildcard_translator(token);
			(*token)->next = second_backup;
		}
		if ((*token)->next == NULL)
			return ;
		(*token) = (*token)->next;
	}
}

// return이 해석된거의 마지막 노드, 확장안됐으면 뒤로 넘어가면 안됨(next->token_str == null인지로 확인)
// lexer에서 해석 심볼 안켜고(1, 0 해석 필요한지만 켜주고) 여기서 만들면서 켜기
static t_lx_token	*_interpreter(t_dict dict[], t_lx_token *cur_token)
{
	t_lx_token		*init_token;
	char			*cur_str;

	init_token = cur_token;
	cur_token->next = NULL;
	cur_str = cur_token->token_str;
	while (*cur_str)
	{
		if (interpret_middleware(dict, cur_token, &cur_str, \
					is_interpret_symbol(*cur_str)) == SPERATE && *cur_str)
		{
			while (cur_token->next)
				cur_token = cur_token->next;
			cur_token->next = make_token_node(NULL, WORD);
			cur_token->next->interpret_symbol |= NEED_TRANSLATE;
		}
		while (cur_token->next)
			cur_token = cur_token->next;
	}
	interpret_wildcard_token(&init_token);
	return (init_token);
}

void	interpret_token_data(t_dict dict[], t_lx_token *token)
{
	t_lx_token	*first_backup;

	while (token)
	{
		if (token->interpret_symbol)
		{
			first_backup = token->next;
			token = _interpreter(dict, token);
			token->next = first_backup;
		}
		token = token->next;
	}
}
