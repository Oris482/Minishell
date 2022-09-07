/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:10:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/07 20:55:00 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "liner.h"
#include "myfunc.h"
#include "lexer.h"

#include "../minishell.h"
#include "../liner/liner.h"
#include "../lexer/lexer.h"
#include "../myfunc/myfunc.h"

static void	_handle_encounter_eof(t_oflag *oflag)
{
	if (oflag->quote == QUOTE)
		print_error_not_close("'");
	if (oflag->quote == DQUOTE)
		print_error_not_close("\"");
	if (oflag->parentheses > 0)
		print_error_not_close("(");
	if (oflag->parentheses < 0)
		print_error_syntax(")");
}

static void	_cnt_parentheses_flag(const char c, int *parentheses_flag, \
								int *quote_flag)
{
	if (!*quote_flag)
		*parentheses_flag += (c == '(') - (c == ')');
}

static int	_check_line_oflag(char *line, int *parentheses_flag, \
								int *quote_flag)
{
	while (*line)
	{
		set_quote_flag(*line, quote_flag);
		_cnt_parentheses_flag(*line, parentheses_flag, quote_flag);
		line++;
	}
	return (*parentheses_flag || *quote_flag);
}

char	*liner(t_oflag *oflag)
{
	char			*line;

	ft_memset(oflag, 0, sizeof(t_oflag));
	line = my_readline("minishell$> ");
	if (_check_line_oflag(line, &oflag->parentheses, &oflag->quote))
		_handle_encounter_eof(oflag);
	return (line);
}
