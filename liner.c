/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:10:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "liner.h"
#include "myfunc.h"
#include "lexer.h"

#include "../minishell.h"
#include "../liner/liner.h"
#include "../lexer/lexer.h"
#include "../myfunc/myfunc.h"

static int	_check_line_oflag(char *line, int *parentheses_flag, \
								int *quote_flag)
{
	while (*line)
	{
		set_quote_flag(*line, quote_flag);
		set_parentheses_flag(*line, parentheses_flag, quote_flag);
		line++;
	}
	return (*parentheses_flag || *quote_flag);
}

char	*liner(t_oflag *oflag)
{
	char			*line;

	ft_memset(oflag, 0, sizeof(t_oflag));
	line = my_readline("minishell$> ");
	_check_line_oflag(line, &oflag->parentheses, &oflag->quote);
	return (line);
}
