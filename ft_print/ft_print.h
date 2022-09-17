/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:19:00 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:32:29 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "minishell_info.h"

// origin_put_fd_utils.c
void			ft_putchar_fd(const char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);

// error_utils.c
void			print_error_syntax(char *token);
void			print_error_not_close(char *str);
int				print_error_str(const char *err_cmd, const char *err_arg, \
										const char *custom_msg, int err_code);

#endif
