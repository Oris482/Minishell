/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 09:47:41 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# define QUOTE 0b00000001
# define DQUOTE 0b00000010
# define DOLLAR 0b00000100

enum	e_token_type
{
	WORD = 100,
	NEW_LINE,
	AND,
	AND_IF,
	OR_IF,
	PIPE,
	SEMI,
	RED_IN,
	RED_OUT,
	HERE_DOC,
	RED_APD_OUT,
	PARENTHESES_OPEN,
	PARENTHESES_CLOSE,
	SPACE_SET,
	WILDCARD
};

enum	e_return
{
	ERROR = -1,
	// SUCCESS
};

typedef struct s_oflag
{
	unsigned char	quote;
	unsigned char	parentheses;
}	t_oflag;

#endif
