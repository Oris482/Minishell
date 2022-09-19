/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:46:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 23:00:17 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_H
# define FT_COMMAND_H

# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>

# define OPTION_ERROR	3
# define ARG_ERROR		4

// built-in functions
int				redi_heredoc(char *limiter);
int				redi_middleware(t_lx_token *token);
int				builtin_echo(t_lx_token *token);
int				builtin_cd(t_lx_token *token);
int				builtin_pwd(t_lx_token *token);
int				builtin_exit(t_lx_token *token);
int				builtin_env(t_lx_token *token);
int				builtin_export(t_lx_token *token);
int				builtin_unset(t_lx_token *token);

// about_pipe.c
int				init_pipe(t_tree *tree_node, char set_exit_status_flag);
pid_t			my_fork(void);

// heredoc.c
int				make_tmp_heredoc(t_lx_token *token, char *limiter);
int				handle_redirections_error(const char *cmd, const char *arg);

// heredoc_utils.c
int				make_tmpfile(char **tmpname, int *fd);
void			write_tmp_heredoc(char *limiter, int write_fd);

// builtin_utils.c
int				is_builtin(const char *str);
int				builtin_option_arg_checker(t_lx_token **token);
int				builtin_middleware(t_lx_token *token, int builtin_idx);

// print_env.c
void			print_env(void);
int				print_export(void);

// program.c
void			execute_middleware(t_lx_token *token);

//allow_about_pipe.c
int				my_dup(int fildes);
int				my_dup2(int fildes, int fildes2);
int				my_pipe(int files[2]);
pid_t			my_fork(void);

#endif
