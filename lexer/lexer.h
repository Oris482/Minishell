/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 17:51:45 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>

typedef struct s_file
{
	int				n;
	DIR				*dirp;
	char			*name;
	int				type;
	int				match_flag;
}	t_file;

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

typedef struct s_oflag
{
	int	quote;
	int	parentheses;
	int	and_if;
}	t_oflag;

// debug_function.c
void			print_token_list(t_lx_token *token_list);
void			classify(struct dirent *ent);
void			print_token_next(t_lx_token *token_list);
void			print_token_prev(t_lx_token *token_list);
// lexer.c
int				lexer(t_lx_token **token_head, char *full_line, t_oflag *oflag);

// tokenization_utils.c
void			set_quote_flag(const char c, int *quote_flag);
void			set_parentheses_flag(const char c, int *parentheses_flag, \
															int *quote_flag);
void			set_interpret_symbol(t_lx_token *token_node, char c, \
								int *quote_flag);
// void			set_quote_flag(const char c, unsigned char *quote_flag);
// void			set_parentheses_flag(const char c, \
//                 unsigned char *parentheses_flag, unsigned char *quote_flag);
void			set_token_type(t_lx_token *token_node, char c);
// void			set_interpret_symbol(t_lx_token *token_node, char c, \
//                                                 unsigned char *quote_flag);

// interpreter.c
void			interpreter(t_lx_token *token);
unsigned char	find_interpret_symbol(char **token_str, \
												unsigned char target);
// interpreter_middleware.c
void			interpret_middleware(t_lx_token *token, char *chunk, \
											unsigned char symbol_type);
// interpreter_make_chunk.c
char			*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type);
// compress_target_char.c
char			*compress_target_char(char *target_str, const char target);
// wildcard_translator.c
void			wildcard_translator(t_lx_token **cur);
// dirent_utils.c
t_file			*get_files_cur_pwd(const char *cur_pwd, char dir_flag);
// find_files.c
int				is_matching_file(char *input, t_file *const files);
void			recursive_find_files(t_lx_token **cur, int cur_level, \
											char *pwd, char **splited);
// find_files_utils.c
char			*path_plus_filename(char *pwd, t_file *files, int idx, \
														int dir_flag);
int				get_target_level(char **splited);
// interpreter_make_chunk.c
char			*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type);

// make_node.c
t_lx_token	*connect_token(t_lx_token *token_head, t_lx_token *cur);

unsigned int	check_syntax_error(t_lx_token *head);
#endif
