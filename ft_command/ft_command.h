/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:46:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 22:00:53 by jaesjeon         ###   ########.fr       */
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
int				make_tmp_heredoc(t_lx_token *token, char *limiter);
int				redi_middleware(t_lx_token *token);
int				redi_heredoc(char *limiter);
int				is_builtin(const char *str);
int				builtin_option_arg_checker(t_lx_token **token);
int				builtin_echo(t_lx_token *token);
int				builtin_cd(t_lx_token *token);
int				builtin_pwd(t_lx_token *token);
int				builtin_exit(t_lx_token *token);
int				builtin_env(t_lx_token *token);
int				builtin_export(t_lx_token *token);
int				builtin_unset(t_lx_token *token);

unsigned char	ft_atouc(char *str);

// program.c
void			execute_middleware(t_lx_token *token);
#endif
