/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_minsuki.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:31:14 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 15:23:28 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "lexer.h"




void dquote_translater(t_lx_token *cur, char *chunk)
{
	pos = ft_strchr('$');
	cur->interpreted_str = ft_strcpy(chunk, pos);		// 없으면 끝까지 \0주소 반환
	chunk = pos;
	if (chunk = '$')
		dollar_translater(cur, ++chunk, 1);

}

void just_str_translater(, )
{

}

char *env_finder(char *envp[])
{
	gete
	while (*envp)
	{


		envp++;
	}
}

void dollar_translater(t_lx_token *cur, char *chunk, int split_flag)
{
	char	*find_str;
	char	*str_cur;

	find_str = getenv(chunk);
	if (!find_str || !*find_str)						// 해당 환경 변수가 없다면
		return ;
	str_cur = find_str;
	while (*str_cur)
	{
		if (!split_flag && ft_isspace(*str_cur))
			break ;						// 처음 노드까지만 찾기
		str_cur++;
	}
	ft_strjoin_self(cur->interpreted_str, ft_strcpy(find_str, str_cur));
	// if (*str_cur == '\0')
		// return ;
	while (*str_cur)
	{
		if (ft_isspace(*str_cur) && str_cur++)
			continue ;
		find_str = str_cur;
		while (*str_cur && !ft_isspace(*str_cur))
			str_cur++;
		cur->next = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
		cur->next->interpreted_str = ft_strcpy(find_str, str_cur);
		cur = cur->next;
	}
}

void interpreter(t_lx_token *cur, char *envp[])
{


	ft_strchr(")
	if
	translate(cur, quote_sign)
		if
	translate(cur, parentheses_sign)
		if
	translate(cur, dollar_sign)

}

