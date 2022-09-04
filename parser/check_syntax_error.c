/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:24:20 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 16:58:27 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	_check_operator_syntax(t_lx_token **token)
{
	const t_lx_token	*prev_token = (*token)->prev;
	const t_lx_token	*next_token = (*token)->next;

	if (prev_token && next_token && prev_token->token_type != AND_IF \
		&& prev_token->token_type != OR_IF && prev_token->token_type != PIPE \
		&& prev_token->token_type != PARENTHESES_OPEN)
		return (SUCCESS);
	printf("syntax error near unexpected token `%s'\n", get_token_str(*token));
	return (FALSE);
}

static int	_check_redirect_syntax(t_lx_token **token)
{
	const t_lx_token	*next_token = (*token)->next;
	char				*err_token_str;

	err_token_str = "newline";
	if (next_token)
	{
		if (next_token->token_type == WORD)
			return (SUCCESS);
		err_token_str = get_token_str(next_token);
	}
	printf("syntax error near unexpected token `%s'\n", err_token_str);
	return (FALSE);
}

static int	_check_parentheses_syntax(t_lx_token **token, \
										int *parentheses_counter)
{
	const t_lx_token	*prev_token = (*token)->prev;

	if ((*token)->token_type == PARENTHESES_OPEN)
	{
		(*parentheses_counter)++;
		if (!prev_token || prev_token->token_type != WORD)
			return (SUCCESS);
	}
	else
	{
		(*parentheses_counter)--;
		if (*parentheses_counter >= 0 && prev_token \
				&& prev_token->token_type == WORD)
			return (SUCCESS);
	}
	printf("syntax error near unexpected token `%s'\n", get_token_str(*token));
	return (FALSE);
}

static unsigned int	_check_syntax_middleware(t_lx_token **token, \
												int *parentheses_counter)
{
	const int	token_type = (*token)->token_type;
	int			is_valid;

	if (token_type == AND_IF || token_type == OR_IF || token_type == PIPE)
		is_valid = _check_operator_syntax(token);
	else if (token_type == RED_IN || token_type == RED_OUT \
		|| token_type == HERE_DOC || token_type == RED_APD_OUT)
		is_valid = _check_redirect_syntax(token);
	else if (token_type == PARENTHESES_OPEN || token_type == PARENTHESES_CLOSE)
		is_valid = _check_parentheses_syntax(token, parentheses_counter);
	return (is_valid);
}

unsigned int	check_syntax_error(t_lx_token *cur_node)
{
	const int	head_token_type = cur_node->token_type;
	int			parentheses_counter;

	if (head_token_type == PIPE || head_token_type == AND_IF \
		|| head_token_type == OR_IF || head_token_type == PARENTHESES_CLOSE)
	{
		printf("syntax error near unexpected token `%s'\n", get_token_str(cur_node));
		return (SYNTAX_ERROR_EXIT_CODE);
	}
	cur_node = cur_node->next;
	parentheses_counter = 0;
	while (cur_node)
	{
		if (cur_node->token_type != WORD && _check_syntax_middleware(&cur_node, \
													&parentheses_counter) == FALSE)
			return (SYNTAX_ERROR_EXIT_CODE);
		cur_node = cur_node->next;
	}
	return (SUCCESS);
}