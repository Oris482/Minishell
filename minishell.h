/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 15:44:51 by minsuki2         ###   ########.fr       */
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

# define TRUE 1
# define SUCCESS 1
# define FALSE 0

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

size_t	ft_strlen(const char *s);
char	*ft_strcpy(const char *start, const char *end);
unsigned char	is_quote(const char c);
unsigned char	is_env_prefix(const char c);
void			set_quote_flag(const char c, unsigned char *quote_flag);
void			set_parentheses_flag(const char c, unsigned char *parentheses_flag
		, unsigned char *quote_flag);
int				ft_isspace(const char c);
int		 ft_strjoin_self(char **str, char *add);
#endif
