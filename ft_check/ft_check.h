/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:15:28 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:41:41 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECK_H
# define FT_CHECK_H
# include "minishell_info.h"

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

#endif
