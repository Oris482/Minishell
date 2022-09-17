/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:46:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 22:41:03 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_H
# define FT_COMMAND_H

# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>

// built-in functions
int				redi_middleware(t_lx_token *token);
int				redi_heredoc(char *limiter);
int				builtin_echo(t_lx_token *token);
int 			builtin_cd(t_lx_token *token);
int 			builtin_pwd(void);
int				builtin_exit(t_lx_token *token);
int				builtin_env(t_lx_token *token);
int				builtin_export(t_lx_token *token);
int				builtin_unset(t_lx_token *token);

// program.c
void			execute_middleware(t_lx_token *token);
#endif
