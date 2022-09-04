/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:55:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 17:20:33 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "myfunc.h"

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

t_lx_token	*set_token(char **line, t_oflag *oflag, char *envp[])
{
	t_lx_token	*token_node;
	const int	token_split_flag = is_token_seperator(**line);
	const char	*str_startpoint = *line;

	token_node = (t_lx_token *)my_calloc(1, sizeof(t_lx_token));
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

int	lexer(t_lx_token **token_head, char *full_line, char *envp[])
{
	t_lx_token	*token_cur;
	t_oflag		oflag;

	oflag.quote = 0;
	oflag.and_if = 0;
	while (*full_line || token_cur)
	{
		if (ft_isspace(*full_line) && full_line++)
			continue ;
		if (*token_head == NULL)
		{
			*token_head = set_token(&full_line, &oflag, envp);
			token_cur = *token_head;
		}
		else if (*full_line && token_cur->next == NULL)
			token_cur->next = set_token(&full_line, &oflag, envp);
		else
			token_cur = connect_token(*token_head, token_cur);
	}
	return (SUCCESS);
}
