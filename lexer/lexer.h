/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/30 23:33:37 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>

# define UNDEFINED 0

typedef struct s_lx_token
{
	char				*token_str;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	int					pass_flag;
	struct s_lx_token	*next;
}	t_lx_token;

typedef struct s_file
{
	int				n;
	DIR				*dirp;
	char			*name;
	int				type;
	int				match_flag;
} t_file;

int		lexer(t_lx_token **token_head, char *full_line, char *envp[]);
void	interpreter(t_lx_token *token);
void	print_token_list(t_lx_token *token_list);
t_file	*get_files_cur_pwd(const char *cur_pwd, int dir_flag);
int 	is_matching_file(char *input, t_file  * const files);
unsigned char	find_interpret_symbol(char **token_str, \
												unsigned char target);
char	*make_chunk_by_symbol(char **token_str, \
					char *str_startpoint, unsigned char *symbol_type);

#endif
