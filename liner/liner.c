/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:10:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/04 16:36:14 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "liner.h"

static void	_handle_encounter_eof(char *line, t_oflag *oflag)
{
	(void)line;
	if (oflag->quote == QUOTE)
		printf("Not closed `''\n");
	if (oflag->quote == DQUOTE)
		printf("Not closed `\"'\n");
	if (oflag->parentheses)
		printf("Not closed `('\n");
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
	char			*tmp_line;

	oflag->quote = 0;
	oflag->parentheses = 0;
	line = readline("minishell$> ");
	if (!line)
	{
		write(STDOUT_FILENO, "BYE\n", 4);
		exit(0);
	}
	i = _check_line_oflag(line, &oflag->parentheses, &oflag->quote);
	// while (oflag->quote || oflag->parentheses)
	// {
	// 	ft_strjoin_self(&line, "\n");
	// 	tmp_line = readline("> ");
	// 	printf("<<<<<%s>>>>>\n", tmp_line);
	// 	if (ft_strjoin_self(&line, tmp_line) == ERROR)
	// 		break ;
	// 	i += _check_line_oflag(line + i, &oflag->parentheses, &oflag->quote);
	// }
	_handle_encounter_eof(line, oflag);
	return (line);
}
