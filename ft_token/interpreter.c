/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:44:22 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/21 22:44:52 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"
#include "ft_check.h"
#include "ft_string.h"
#include "ft_alloc.h"

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
	else if (symbol_type == WILDCARD) // * 붙여주면서 심볼 켜주기만 한다.
		ret = wildcard_translator(cur_token, cur_str);
	else if (symbol_type & TILDE && func_level == 1)
		ret = tilde_translator(*cur_token, cur_str);
	if (ret != ERROR)
		return (ret);
	ft_chrjoin_myself(&(*cur_token)->interpreted_str, **cur_str);
	(*cur_str)++;
	return (NOT_SPERATE);
}
/* *line 26
 * 달러 다음 큰 따옴표 순으로 if 문을 작성해야 함
 * ㄴ DOLLAR를 만나서 DQUOTE에 들어갈 수 는 없지만
 * ㄴ DQUOTE를 만나서 DOLLAR에 들어갈 수 있음
 */

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
			cur_token->next = make_token_node(NULL, WORD);
			cur_token = cur_token->next;
			cur_token->interpret_symbol = backup_interpret_symbol;
		}
	}
	// 첫 노드(init_node)부터 쭉 와일드 카드 체크
	while (cur_token->next->token_str == NULL)
		cur_token = cur_token->next;
	return (cur_token);
}
