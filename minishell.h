/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:08:52 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:44:44 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
// # include <sys/stat.h>

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

#endif
