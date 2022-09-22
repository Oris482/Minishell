/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/22 17:36:41 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"

int	prepare_wildcard_translate(t_lx_token **cur_token)
{
	(*cur_token)->interpret_symbol |= WILDCARD;
	return (ERROR);
}

int	interpret_middleware_is_sperated(t_lx_token **cur_token, \
			char **cur_str, unsigned char symbol_type, int func_level)
{
	int	ret;

	ret = ERROR;
	if (symbol_type & QUOTE && func_level == 1)
		ret = quote_translator(*cur_token, cur_str);
	else if (symbol_type & DOLLAR)
		ret = dollar_translator(cur_token, cur_str, symbol_type);
	else if (symbol_type & DQUOTE && func_level == 1)
		ret = dquote_translator(cur_token, cur_str);
	else if (symbol_type == WILDCARD && func_level == 1)
		ret = prepare_wildcard_translate(cur_token);
	else if (symbol_type & TILDE && func_level == 1)
		ret = tilde_translator(*cur_token, cur_str);
	if (ret != ERROR)
		return (ret);
	ft_chrjoin_myself(&(*cur_token)->interpreted_str, **cur_str, BACK);
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
	t_lx_token	*backup;

	while (*token)
	{
		if ((*token)->interpret_symbol & WILDCARD)
		{
			backup = (*token)->next;
			wildcard_translator(token);
			(*token)->next = backup;
		}
		if ((*token)->next == NULL)
			break ;
		(*token) = (*token)->next;
	}
}

// return이 해석된거의 마지막 노드, 확장안됐으면 뒤로 넘어가면 안됨(next->token_str == null인지로 확인)
// lexer에서 해석 심볼 안켜고(1, 0 해석 필요한지만 켜주고) 여기서 만들면서 켜기
t_lx_token	*interpreter(t_lx_token *cur_token)
{
	const t_lx_token	*init_node = cur_token;
	char				*cur_str;
	const int			backup_interpret_symbol = cur_token->interpret_symbol;

	cur_str = cur_token->token_str;
	while (*cur_str)
	{
		if (interpret_middleware_is_sperated(&cur_token, &cur_str, \
							is_interpret_symbol(*cur_str), 1) == SPERATE)
		{
			interpret_wildcard_token(&cur_token);
			cur_token->next = make_token_node(NULL, WORD);
			cur_token = cur_token->next;
			cur_token->interpret_symbol = backup_interpret_symbol;
		}
	}
	interpret_wildcard_token(&cur_token);
	(void)init_node;
	return (cur_token);
}
