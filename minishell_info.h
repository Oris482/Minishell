/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_info.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:40:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 21:21:13 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INFO_H
# define MINISHELL_INFO_H
# include <dirent.h>

# define A			0
# define B			1
# define F_READ			0
# define F_WRITE		1

# define CHILD_PID		0

# define BACKUP			1
# define RESTORE		2

# define EXPORT_HEAD_MSG	"declare -x "
# define IDX_ONE_OR_MORE	1
# define DICT_MAX		53

# include <dirent.h>
# include <unistd.h>

typedef struct s_pipe
{
	int	fd[2][2];
	int	pipe_cnt;
	int	fork_cnt;
}	t_pipe;

typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}	t_pid_list;

typedef struct s_heredoc_info
{
	int		option;
	char	*limiter;
}	t_heredoc_info;


typedef struct s_dict
{
	char			*name;
	char			*value;
	struct s_dict	*next;
	struct s_dict	*prev;
}	t_dict;


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

typedef struct s_oflag
{
	int	quote;
	int	parentheses;
	int	and_if;
}	t_oflag;

enum	e_interpreted_type
{
	UNDEFINED		=	0b00000000,
	QUOTE			=	0b00000001,
	DQUOTE			=	0b00000010,
	DOLLAR			=	0b00000100,
	WILDCARD		=	0b00001000,
	TILDE			=	0b00010000,
	NEED_TRANSLATE	=	0b01000000
};

enum e_tree_type
{
	TREE_UNDEFINED =	0b00000001,
	TREE_AND =			0b00000010,
	TREE_OR =			0b00000100,
	TREE_PIPE =			0b00001000,
	TREE_CMD =			0b00010000,
	TREE_REDI =			0b00100000,
	TREE_SIMPLE_CMD =	0b01000000,
	TREE_SUBSHELL =		0b10000000,
	TREE_ALL =			0b11111111
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

enum	e_builtin_idx
{
	BI_ECHO = 10,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
};

enum	e_exit_code
{
	SUCCESS_EXIT_CODE = 0,
	GENERAL_EXIT_CODE = 1,
	PERMISSION_EXIT_CODE = 2,
	INVALID_OPTION_EXIT_CODE = 2,
	SIG_DEFAULT_EXIT_CODE = 128,
	NONE_NUMERIC_EXIT_CODE = 255,
	SYNTAX_ERROR_EXIT_CODE = 258
};

enum	e_sperate
{
	NOT_SPERATE,
	SPERATE,
};

enum	e_return
{
	ERROR = -1,
	FALSE,
	SUCCESS,
	TRUE = 1
};

enum	e_order
{
	LESS_THAN = -1,
	EQUAL,
	GREATER_THAN,
};
#endif
