/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 00:54:32 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>

// terminal_setting.c
void			set_init_signal(void);
void			set_int_quit_signal(void *sigint_action, void *sigquit_action);
int				terminal_off_control_chars(void);
int				terminal_on_control_chars(void);

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

// parser_utils.c
void			making_tree_node(t_tree *const cur, \
									unsigned char (*is_tree_type)(int));

// expand_cmd_tree_utils.c
int				redi_to_left(t_tree *cur_tree, t_lx_token **token_data);
void			remain_to_right(t_tree *cur_tree, t_lx_token *token_data);

// executor.c
int				handle_cmd(t_tree *tree_node, char set_exit_status_flag);
int				executor(t_tree *root, char set_exit_status_flag);

// exit_status.c
void			set_exit_status(int status);
int				get_exit_status(void);
int				get_exit_code(int status);

#endif
