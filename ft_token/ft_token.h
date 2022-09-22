/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:33:13 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 15:33:40 by minsuki2         ###   ########.fr       */
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
void			set_interpret_symbol(t_lx_token *token_node);
void			set_token_type(t_lx_token *token_node, char c);
void			set_need_translate_symbol(t_lx_token *token_node, char c, \
															int *quote_flag);

// interpreter.c
int				interpret_middleware(t_lx_token *cur_token, char **cur_str, \
									unsigned char symbol_type, int func_level);
void			interpret_wildcard_token(t_lx_token **token);
void			interpret_token_data(t_lx_token *token);

// interpreter_make_chunk.c
char			*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type);
// compress_target_char.c
char			*compress_target_char(char *target_str, const char target);

// quote_tilde_translator.c
int				quote_translator(t_lx_token *cur_token, char **cur_str);
int				dquote_translator(t_lx_token *cur, char **cur_str);
int				tilde_translator(t_lx_token *cur_token, char **cur_str);

// dollar_translator.c
int				dollar_translator(t_lx_token *cur_token, \
							char **cur_str, unsigned char symbol_type);
// wildcard_translator.c
int				wildcard_translator(t_lx_token **cur_token);
#endif
