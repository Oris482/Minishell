/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:55:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_info.h"
#include "myfunc.h"

static void	*_handle_encounter_eof(t_oflag *oflag)
{
	if (oflag->quote == QUOTE)
		print_error_not_close("'");
	if (oflag->quote == DQUOTE)
		print_error_not_close("\"");
	if (oflag->parentheses > 0)
		print_error_not_close("(");
	if (oflag->parentheses < 0)
		print_error_syntax(")");
	return (NULL);
}

static int	_check_doubled_operator(char **line)
{
	if (**line == '|' && *(*line + 1) == '|')
		return (OR_IF);
	else if (**line == '&' && *(*line + 1) == '&')
		return (AND_IF);
	else if (**line == '<' && *(*line + 1) == '<')
		return (HERE_DOC);
	else if (**line == '>' && *(*line + 1) == '>')
		return (RED_APD_OUT);
	return (FALSE);
}

static int	_make_operator(t_lx_token *token_node, char **line, int token_type)
{
	const char	*str_startpoint = *line;

	if (token_type == FALSE)
		return (FALSE);
	(*line) += 2;
	token_node->token_str = ft_strcpy(str_startpoint, *line);
	token_node->token_type = token_type;
	return (SUCCESS);
}

t_lx_token	*set_token(char **line, t_oflag *oflag)
{
	t_lx_token	*token_node;
	const int	token_split_flag = is_token_seperator(**line);
	const char	*str_startpoint = *line;

	token_node = make_token_node(NULL, UNDEFINED);
	if (_make_operator(token_node, line, _check_doubled_operator(line)))
		return (token_node);
	while (**line && (oflag->quote || (token_node->token_type == UNDEFINED \
										|| !is_token_seperator(**line))))
	{
		set_quote_flag(**line, &oflag->quote);
		set_token_type(token_node, **line);
		set_interpret_symbol(token_node, **line, &oflag->quote);
		(*line)++;
		if (token_split_flag || (!oflag->quote && **line == '&' \
									&& *(*line + 1) == '&'))
			break ;
	}
	token_node->token_str = ft_strcpy(str_startpoint, *line);
	if (token_node->interpret_symbol)
		interpreter(token_node);
	return (token_node);
}

t_lx_token	*lexer(char *full_line, t_oflag *oflag)
{
	t_lx_token	*token_head;
	t_lx_token	*token_cur;

	if (oflag->parentheses || oflag->quote)
		return (_handle_encounter_eof(oflag));
	token_head = NULL;
	while (*full_line || token_cur)
	{
		if (ft_isspace(*full_line) && full_line++)
			continue ;
		if (token_head == NULL)
		{
			token_head = set_token(&full_line, oflag);
			token_cur = token_head;
		}
		else if (*full_line && token_cur->next == NULL)
			token_cur->next = set_token(&full_line, oflag);
		else
			token_cur = connect_token(token_head, token_cur);
	}
	return (token_head);
}
