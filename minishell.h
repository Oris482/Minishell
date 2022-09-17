/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:53:56 by jaesjeon         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>




/* ft_string
// origin_str_utils.c
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);

// origin_str_utils2.c
void			*ft_memset(void *b, int c, size_t len);
int				ft_strcmp(char *s1, char *s2);
char			*ft_itoa(int num);
char			*ft_strdup(const char *s1);

// custom_str_utils.c
size_t			ft_strcnt(const char *s, const char c);
char			*ft_strsjoin(char const *s1, char const *s2, char const *s3);
char			*ft_strjoin_self(char **str, char *add);
char			*ft_strchr_null(const char *s, int c);
char			*ft_strrchr_right_away(const char *s, int c, char *const end);

// custom_str_utils2.c
int 			ft_strcmp_ignore_capital(char *ref, char *target);
char			*ft_strcpy(const char *start, const char *end);
char			*ft_chr_to_str(char c);
*/

/* ft_check
// check_char_utils.c
int				ft_isspace(const char c);
unsigned char	is_target_char(const char c, const char target);
int				is_token_seperator(const char c);
int				is_metacharacter(const char c);
int     		is_redi_token(t_lx_token *token);

// check_interpret_symbol_utils.c
unsigned char	is_quote(const char c);
unsigned char	is_dollar(const char c);
unsigned char	is_wildcard(const char c);
unsigned char	is_tilde(const char c);
unsigned char	is_interpret_symbol(const char c);
*/

/* ft_token
// token_list_utils.c
t_lx_token  	*cut_front_token(t_lx_token *cur_token);
t_lx_token		*cut_back_token(t_lx_token *cur_token);
t_lx_token  	*pop_token(t_lx_token **cur_token, t_lx_token *end_token);
void			merge_linked_list(t_lx_token *dst, t_lx_token *src);
t_lx_token		*connect_token(t_lx_token *token_head, t_lx_token *cur);

// token_node_utils.c
t_lx_token		*make_token_node(char *token_str, int token_type);
char			*get_token_str(const t_lx_token *token);
t_lx_token		*get_last_token(t_lx_token *token);

// tokenization_utils.c
void			set_quote_flag(const char c, int *quote_flag);
void			set_parentheses_flag(const char c, int *parentheses_flag, \
															int *quote_flag);
void			set_interpret_symbol(t_lx_token *token_node, char c, \
								int *quote_flag);
void			set_token_type(t_lx_token *token_node, char c);

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
// interpreter_make_chunk.c
char			*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type);

*/

/* ft_print
// origin_put_fd_utils.c
void			ft_putchar_fd(const char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);

// error_utils.c
void			print_error_syntax(char *token);
void			print_error_not_close(char *str);
int				print_error_str(const char *err_cmd, const char *err_arg, \
										const char *custom_msg, int err_code);
*/

/* ft_free

*/

/* ft_tree
// tree_utils.c
unsigned char	is_tree_and_or(int token_type);
unsigned char	is_tree_pipe(int token_type);
t_tree			*make_tree_node(int type, t_tree *parent_tree, t_lx_token *data);
void    		tree_traversal(t_tree *cur_tree, int tree_type, \
											void (*handler)(t_tree *));
*/

/* ft_env
// envp_utils.c
void			char_dimen2_to_lst(char *envp[]);
void			envp_to_dict(char *envp[]);
char		 	**dict_to_envp(void);
int				chr_to_idx(char c);
t_dict			*make_envp_node(char *name, char *value, t_dict *next, t_dict *prev);
void			dict_lstadd_last(t_dict *head, t_dict *new);
void			dict_lstadd_next(t_dict *cur, t_dict *new);
void			dict_lstadd_order(t_dict *head, t_dict *new);
int				check_match_word(const char *word1, const char *word2);
int				check_vaild_env_name(char *name);

// dict_utils.c
int				count_dict(void);
t_dict			*find_dict(t_dict *cur, const char *name);
void			erase_dict(char *name);
t_dict			*add_dict(char *name, char *value, char *merge_str);
t_dict			*put_dict(char *name, char *value);

// dict_utils2.c
t_dict			*get_last_dict(t_dict *dic);
t_dict			*get_first_dict(t_dict *dic);

// about_env.c
char			*my_getenv(const char *name);

*/ 

/* ft_cmd

*/

/* ft_file
// about_dir
DIR				*my_opendir(const char *name);
struct dirent	*my_readdir(DIR *dirp);
int				my_closedir(DIR *dirp);

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
*/

/* minishell.h
// terminal_setting.c
void			signal_handler(void);
int				terminal_off_control_chars(void);

// liner.c
char			*liner(t_oflag *oflag);

// about_readline
char			*my_readline(const char *prompt);

// lexer.c
t_lx_token		*lexer(char *full_line, t_oflag *oflag);

// check_syntax_error.c
unsigned int	check_syntax_error(t_lx_token *head);

// parser.c
t_tree			*parser(t_lx_token *head);

// executor.c
int				executor(t_tree *root, char set_exit_status_flag);

// exit_status.c
void			set_exit_status(int status);
int				get_exit_status(void);
*/

/////////////////////////////////////////////

/* ft_debug
// debug_print_evnp.c
int	print_dictionary_lst();
int	print_strs(char *strs[]);

// debug_print_tree.c
void 			print_ascii_tree(t_tree * t);

// debug_function.c
void			print_token_list(t_lx_token *token_list);
void			classify(struct dirent *ent);
void			print_token_next(t_lx_token *token_list);
void			print_token_prev(t_lx_token *token_list);
*/

#endif
