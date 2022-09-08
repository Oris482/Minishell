/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/08 17:57:03 by jaesjeon         ###   ########.fr       */
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
# include <dirent.h>

# define UNDEFINED		0b00000000
# define QUOTE			0b00000001
# define DQUOTE			0b00000010
# define DOLLAR			0b00000100
# define WILDCARD		0b00001000
# define TILDE			0b00010000

typedef struct s_lx_token
{
	char				*token_str;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	int					pass_flag;
	struct s_lx_token	*prev;
	struct s_lx_token	*next;
}	t_lx_token;

typedef struct s_file
{
	int				n;
	DIR				*dirp;
	char			*name;
	int				type;
	int				match_flag;
}	t_file;

typedef struct s_tree
{
	unsigned char	type;
	t_lx_token		*token_data;
	struct s_tree	*parent_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

enum e_tree_type
{
	TREE_UNDEFINED =	0b00000001,
	TREE_AND = 			0b00000010,
	TREE_OR =			0b00000100,
	TREE_PIPE =			0b00001000,
	TREE_CMD =			0b00010000,
	TREE_REDI =			0b00100000,
	TREE_SIMPLE_CMD =	0b01000000,
	TREE_SUBSHELL =		0b10000000,
	TREE_ALL = 			0b11111111
};

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
	GENERAL_EXIT_CODE = 1,
	SYNTAX_ERROR_EXIT_CODE = 258
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
	int	quote;
	int	parentheses;
	int	and_if;
}	t_oflag;

// origin_str_utils.c
size_t			ft_strlen(const char *s);
char			*ft_strcpy(const char *start, const char *end);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);

// origin_str_utils2.c
void			*ft_memset(void *b, int c, size_t len);

// origin_put_fd_utils.c
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);

// custom_str_utils.c
size_t			ft_strcnt(const char *s, const char c);
char			*ft_strsjoin(char const *s1, char const *s2, char const *s3);
int				ft_strjoin_self(char **str, char *add);
char			*ft_strchr_null(const char *s, int c);
char			*ft_strrchr_right_away(const char *s, int c, char *const end);
// check_char_utils.c
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
// terminal_setting.c
void			signal_handler(void);
int				terminal_off_control_chars(void);
// linked_list_utils.c
t_lx_token  	*cut_front_node(t_lx_token *cur_node);
t_lx_token		*cut_back_node(t_lx_token *cur_node);
t_lx_token  	*pop_node(t_lx_token **cur_node, t_lx_token *end_node);
void			merge_linked_list(t_lx_token *dst, t_lx_token *src);
// minishell_utils.c
char			*get_token_str(const t_lx_token *token);
t_lx_token		*get_last_node(t_lx_token *token);
void			*make_new_node(size_t size);
t_lx_token		*make_new_token(char *token_str, int token_type, t_lx_token *prev);
//error_utils.c
void			print_error_syntax(char *token);
void			print_error_not_close(char *str);
// free_utils.c
t_lx_token 		*lst_fclean(t_lx_token *cur_list);
void			tree_free(t_tree *cur_tree);
#endif
