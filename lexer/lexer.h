/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/25 19:11:11 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>

# define UNDEFINED 0

typedef struct s_lx_token
{
	char				*token_str;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	struct s_lx_token	*next;
}	t_lx_token;

typedef struct s_file
{
	char	*name;
	int		file_type;
	char	*file_pwd;
} t_file;

int		lexer(t_lx_token **token_head, char *full_line, char *envp[]);
void	interpreter(t_lx_token *token);
void	print_token_list(t_lx_token *token_list);

#endif
