/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tilde_translator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:29:22 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 21:55:51 by minsuki2         ###   ########.fr       */
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

int	quote_translator(t_lx_token *cur_token, char **cur_str)
{
	char	*end;

	/*
	 * DQUOTE에 들어갔다가 여기에 들어오는 QUOTE를 무시하기 위해서
	 */
	(*cur_str)++;
	end = ft_strchr(*cur_str, '\'');
	ft_strjoin_self_add_free(&cur_token->interpreted_str, \
											ft_strcpy(*cur_str, end));
	(*cur_str) = end + 1;
	cur_token->interpret_symbol |= QUOTE;
	return (NOT_SPERATE);
}

int	dquote_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str)
{
	char	*end;

	/*
	if (symbol_type != DQUOTE)
		return (ERROR);
	 * 위의 if문은 사실상 필요없음
	 * => DQUOTE를 만나고 나서 DQUOTE를중복으로 만날 수 없기 때문
	 * => '"'의 경우는 ft_strcpy로 냅다 복사하기 때문에 (interpret_middleware_is_sperated 사용 x)
	 */
	(*cur_str)++;
	end = ft_strchr(*cur_str, '\"');
	while (*cur_str != end)
		interpret_middleware(dict, cur_token, cur_str, \
				DQUOTE | is_interpret_symbol(**cur_str));
	*cur_str = end + 1;
	cur_token->interpret_symbol |= DQUOTE;
	return (NOT_SPERATE);
}

int	tilde_translator(t_dict dict[], t_lx_token *cur_token, char **cur_str)
{
	// <- 일단 앞으로 아니면 앞으로 옮기지 x
	// 첫노드가 아니면 나가기 + 이미 interpreted_str에 앞 문자열이 있으면 붙이고 나가기
	if (!cur_token->token_str || cur_token->interpreted_str)
		return (ERROR);
	/*
	 * '\0' 아니면서 '/'아니면 종료
	 */
	else if (*(cur_token->token_str + 1) != '\0' \
										&& *(cur_token->token_str + 1) != '/')
		return (ERROR);
	ft_strjoin_self(&cur_token->interpreted_str, my_getenv(dict, "HOME"));
	(*cur_str)++;
	cur_token->interpret_symbol |= TILDE;
	return (NOT_SPERATE);
}
