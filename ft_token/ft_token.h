/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:33:13 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 23:49:06 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

# include <unistd.h>

// token_list_utils.c
t_lx_token		*cut_front_token(t_lx_token *cur_token);
t_lx_token		*cut_back_token(t_lx_token *cur_token);
t_lx_token		*pop_token(t_lx_token **cur_token, t_lx_token *end_token);
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
#endif