/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:38:01 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 23:51:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_token.h"

t_lx_token	*cut_front_token(t_lx_token *cur_token)
{
	t_lx_token *const	last_token = get_last_token(cur_token);
	t_lx_token *const	new_last_token = cur_token->prev;

	if (cur_token->prev == last_token)
		return (NULL);
	cur_token->prev = last_token;
	cur_token = new_last_token;
	cur_token->next = NULL;
	while (cur_token->prev != last_token)
		cur_token = cur_token->prev;
	cur_token->prev = new_last_token;
	return (cur_token);
}

t_lx_token	*cut_back_token(t_lx_token *cur_token)
{
	t_lx_token *const	last_token = get_last_token(cur_token);
	t_lx_token *const	new_last_token = cur_token;
	t_lx_token *const	ret_token = cur_token->next;

	if (cur_token == last_token)
		return (NULL);
	ret_token->prev = last_token;
	cur_token->next = NULL;
	while (cur_token->prev != last_token)
		cur_token = cur_token->prev;
	cur_token->prev = new_last_token;
	return (ret_token);
}

t_lx_token	*pop_token(t_lx_token **cur_token, t_lx_token *end_token)
{
	t_lx_token *const	start_token = *cur_token;
	t_lx_token *const	last_token = get_last_token(*cur_token);

	*cur_token = end_token->next;
	if (start_token->prev == last_token && end_token == last_token)
		return ((t_lx_token *)start_token);
	if (start_token->prev == last_token)
		return (cut_front_token(end_token->next));
	else if (end_token == last_token)
		return (cut_back_token(start_token->prev));
	else
	{
		start_token->prev->next = end_token->next;
		end_token->next->prev = start_token->prev;
		start_token->prev = end_token;
		end_token->next = NULL;
	}
	return (start_token);
}

void	merge_linked_list(t_lx_token *dst, t_lx_token *src)
{
	const t_lx_token	*dst_last_token = get_last_token(dst);
	const t_lx_token	*src_last_token = get_last_token(src);

	dst->prev->next = src;
	dst->prev = (t_lx_token *)src_last_token;
	src->prev = (t_lx_token *)dst_last_token;
}

t_lx_token	*connect_token(t_lx_token *token_head, t_lx_token *cur)
{
	if (cur->next)
		cur->next->prev = cur;
	else
		if (token_head)
			token_head->prev = cur;
	return (cur->next);
}
