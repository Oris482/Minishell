/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:10:39 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 11:11:17 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include "minishell.h"
#include "liner.h"


void	set_parentheses_flag(const char c, unsigned char *parentheses_flag, unsigned char *quote_flag)
{
	if (!*quote_flag)									// 통일성을 위해 주소로?
	{
		if (c == '(' && !*parentheses_flag)
			*parentheses_flag ^= PARENTHESES_OPEN;
		else if (c == ')')
		{
			if (*parentheses_flag == PARENTHESES_OPEN)
				*parentheses_flag ^= PARENTHESES_OPEN;
			// else
			//     exit(1);
		}
	}
}

void	set_quote_flag(const char c, unsigned char *quote_flag)
{
	if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
		*quote_flag ^= QUOTE;
	else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
		*quote_flag ^= DQUOTE;
}

int	check_line_oflag(char *line, unsigned char *parentheses_flag, unsigned char *quote_flag)
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

void tmp_debug_print(char *line, t_oflag *oflag);

char *line_handler(void)
{
	t_oflag			oflag;
	char			*line;
	int				i;

	oflag.quote = 0;
	oflag.parentheses = 0;
	line = readline("minishell$> ");
	if (!line)
		return (NULL);
	i = check_line_oflag(line, &oflag.parentheses, &oflag.quote);
	while (oflag.quote || oflag.parentheses)			// 둘다 닫혀야 함
	{
		if (ft_strjoin_self(&line, "\n") == ERROR
			|| ft_strjoin_self(&line, readline("> ")) == ERROR)
			break ;
		i += check_line_oflag(line + i, &oflag.parentheses, &oflag.quote);
	}
	tmp_debug_print(line, &oflag);
	return (line);
}

void tmp_debug_print(char *line, t_oflag *oflag)
{
	if (oflag->quote == QUOTE)
		printf("unexpected EOF while looking for matching `''\n");
	if (oflag->quote == DQUOTE)
		printf("unexpected EOF while looking for matching `\"'\n");
	if (oflag->parentheses)
		printf("unexpected EOF while looking for matching `('\n");
	if (!oflag->quote && !oflag->parentheses)
		printf("%s\n", line);
}
