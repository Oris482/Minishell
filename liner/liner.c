/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:10:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/03 17:17:53 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "liner.h"

static void	_handle_encounter_eof(char *line, t_oflag *oflag)
{
	(void)line;
	if (oflag->quote == QUOTE)
		printf("unexpected EOF while looking for matching `''\n");
	if (oflag->quote == DQUOTE)
		printf("unexpected EOF while looking for matching `\"'\n");
	if (oflag->parentheses)
		printf("unexpected EOF while looking for matching `('\n");
}

static int	_check_line_oflag(char *line, unsigned char *parentheses_flag, \
								unsigned char *quote_flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		set_quote_flag(line[i], quote_flag);
		set_parentheses_flag(line[i], parentheses_flag, quote_flag);
		++i;
	}
	return (i);
}

char	*line_handler(t_oflag *oflag)
{
	char			*line;
	char			*line_after_newline;
	int				i;

	oflag->quote = 0;
	oflag->parentheses = 0;
	line = readline("minishell$> ");
	if (!line)
	{
		write(STDOUT_FILENO, "BYE\n", 4);
		exit(0);
	}
	i = _check_line_oflag(line, &oflag->parentheses, &oflag->quote);
	while (oflag->quote || oflag->parentheses)
	{
		if (ft_strjoin_self(&line, "\n") == ERROR
			|| ft_strjoin_self(&line, readline("> ")) == ERROR)
			break ;
		i += _check_line_oflag(line + i, &oflag->parentheses, &oflag->quote);
	}
	_handle_encounter_eof(line, oflag);
	return (line);
}
