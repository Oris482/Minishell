/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_middleware.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:03:50 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/27 10:59:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_token.h"
#include "ft_print.h"
#include "ft_check.h"

static int	_check_word_syntax(t_lx_token *token)
{
	t_lx_token			*target;

	if (token->prev == NULL || token->prev->prev == NULL)
		return (SUCCESS);
	if (token->prev->token_type == PARENTHESES_CLOSE)
		return (print_error_syntax(get_token_str(token)));
	if (token->prev->token_type != WORD)
		return (SUCCESS);
	if (token->prev->token_str != NULL)
		target = token->prev->prev;
	else
	{
		target = token->prev;
		while (token->token_str == NULL)
			target = target->prev;
		target = target->prev;
	}
	if (is_redi_token(target))
		target = target->prev;
	if (target == NULL || target->token_type != PARENTHESES_CLOSE)
		return (SUCCESS);
	return (print_error_syntax(get_token_str(token)));
}

static int	_check_operator_syntax(t_lx_token *token)
{
	const t_lx_token	*prev_token = token->prev;
	const t_lx_token	*next_token = token->next;

	if (prev_token && next_token && prev_token->token_type != AND_IF \
		&& prev_token->token_type != OR_IF && prev_token->token_type != PIPE \
		&& prev_token->token_type != PARENTHESES_OPEN)
		return (SUCCESS);
	return (print_error_syntax(get_token_str(token)));
}

static int	_check_redirect_syntax(t_lx_token *token)
{
	const t_lx_token	*next_token = token->next;
	char				*err_token_str;

	err_token_str = "newline";
	if (next_token)
	{
		if (next_token->token_type == WORD)
			return (SUCCESS);
		err_token_str = get_token_str(next_token);
	}
	return (print_error_syntax(err_token_str));
}

static int	_check_parentheses_syntax(t_lx_token *token, \
										int *parentheses_counter)
{
	t_lx_token *const	prev_token = token->prev;
	t_lx_token			*target;

	if (token->token_type == PARENTHESES_OPEN)
	{
		if (prev_token == NULL \
					|| prev_token->token_type != WORD)
			return (SUCCESS);
		else if (prev_token && prev_token->prev != NULL)
		{
			target = (t_lx_token *)prev_token;
			while (target->token_str == NULL)
				target = target->prev;
			if (target->token_type == WORD && \
				target->prev != NULL && is_redi_token(target->prev))
				return (SUCCESS);
		}
	}
	else if (*parentheses_counter >= 0 && (prev_token->token_type == WORD \
			|| prev_token->token_type == PARENTHESES_CLOSE))
		return (SUCCESS);
	return (print_error_syntax(get_token_str(token)));
}

unsigned int	check_syntax_middleware(t_lx_token *token, \
												int *parentheses_counter)
{
	const int	token_type = token->token_type;
	int			is_valid;

	if (token_type == WORD)
	{
		if (token->token_str != NULL)
			is_valid = _check_word_syntax(token);
		else
			is_valid = SUCCESS;
	}
	else if (token_type == AND_IF || token_type == OR_IF || token_type == PIPE)
		is_valid = _check_operator_syntax(token);
	else if (token_type == RED_IN || token_type == RED_OUT \
		|| token_type == HERE_DOC || token_type == RED_APD_OUT)
		is_valid = _check_redirect_syntax(token);
	else if (token_type == PARENTHESES_OPEN || token_type == PARENTHESES_CLOSE)
		is_valid = _check_parentheses_syntax(token, parentheses_counter);
	else
		is_valid = UNDEFINED;
	return (is_valid);
}
