/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:42:47 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/25 14:22:26 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENVIRON_H
# define FT_ENVIRON_H

# include <unistd.h>

// about_env.c
void			char_dimen2_to_lst(char *envp[]);
void			envp_to_dict(t_dict dict[], char *envp[]);
char			**dict_to_envp(t_dict dict[]);
int				chr_to_dict_idx(char c);
char			*my_getenv(t_dict dict[], const char *name);

// dict_node_utils.c
t_dict			*make_envp_node(char *name, char *value, \
												t_dict *next, t_dict *prev);
void			dict_lstadd_order(t_dict *head, t_dict *new);
int				compare_order_dict(const t_dict *next, const t_dict *new);

// dict_utils.c
int				count_dict(t_dict dict[]);
t_dict			*find_dict(t_dict *cur, const char *name);
void			erase_dict(t_dict dict[], char *name);
t_dict			*add_dict(t_dict dict[], char *name, char *value, \
															char *merge_str);
t_dict			*put_dict(t_dict dict[], char *name, char *value);

// dict_utils2.c
t_dict			*get_last_dict(t_dict *dic);
t_dict			*get_first_dict(t_dict *dic);
int				chr_to_dict_idx(char c);
int				check_valid_env_name(char *name);
int				check_match_word(const char *word1, const char *word2);
#endif
