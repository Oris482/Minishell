/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/23 09:45:52 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>

# define TRUE 1
# define SUCCESS 1
# define FALSE 0

// # define QUOTE 0b00000001
// # define DQUOTE 0b00000010
// # define DOLLAR 0b00000100

# define UNDEFINED 0

// enum	e_token_type
// {
//     WORD = 100,
//     NEW_LINE,
//     AND,
//     AND_IF,
//     OR_IF,
//     PIPE,
//     SEMI,
//     RED_IN,
//     RED_OUT,
//     HERE_DOC,
//     RED_APD_OUT,
//     PARENTHESES_OPEN,
//     PARENTHESES_CLOSE,
//     SPACE_SET,
//     WILDCARD
// };

typedef struct s_lx_token
{
	char				*token_str;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	struct s_lx_token	*next;
}	t_lx_token;

t_lx_token	*lexer(t_lx_token *token_head, char *line, unsigned char *quote_flag, unsigned char *parentheses_flag);
void	print_token_list(t_lx_token *token_list);

#endif
