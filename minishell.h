/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/03 23:07:18 by minsuki2         ###   ########.fr       */
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
# include <term.h>
# include "lexer.h"

# define QUOTE 0b00000001
# define DQUOTE 0b00000010
# define DOLLAR 0b00000100
# define WILDCARD 0b00001000
# define TILDE 0b00010000

enum	e_token_type
{
	WORD = 100,
	NEW_LINE,
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
};

enum	e_exit_code
{
	GENERAL_EXIT_CODE = 1
};

enum	e_return
{
	ERROR = -1,
	FALSE,
	SUCCESS,
	TRUE = 1
};

typedef struct s_oflag
{
	unsigned char	quote;
	unsigned char	parentheses;
	unsigned char	and_if;
}	t_oflag;

// origin_str_utils.c
size_t			ft_strlen(const char *s);
char			*ft_strcpy(const char *start, const char *end);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);

// origin_str_utils2.c
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);

// custom_str_utils.c
size_t			ft_strcnt(const char *s, const char c);
char			*ft_strsjoin(char const *s1, char const *s2, char const *s3);
int				ft_strjoin_self(char **str, char *add);
char			*ft_strchr_null(const char *s, int c);
char			*ft_strrchr_right_away(const char *s, int c, char *const end);
// custom_char_utils.c
int				ft_isspace(const char c);
unsigned char	is_target_char(const char c, const char target);
int				is_token_seperator(const char c);
int				is_metacharacter(const char c);
// check_interpret_symbol_utils.c
unsigned char	is_quote(const char c);
unsigned char	is_dollar(const char c);
unsigned char	is_wildcard(const char c);
unsigned char	is_tilde(const char c);
unsigned char	is_interpret_symbol(const char c);
// tokenization_utils.c
void			set_quote_flag(const char c, unsigned char *quote_flag);
void			set_parentheses_flag(const char c, \
				unsigned char *parentheses_flag, unsigned char *quote_flag);
void			set_token_type(t_lx_token *token_node, char c);
void			set_interpret_symbol(t_lx_token *token_node, char c, \
												unsigned char *quote_flag);
// terminal_setting.c
void			signal_handler(void);
int				terminal_off_control_chars(void);
// compress_target_char.c
char			*compress_target_char(char *target_str, const char target);
// wildcard_translator.c
void			wildcard_translator(t_lx_token **cur);
#endif
