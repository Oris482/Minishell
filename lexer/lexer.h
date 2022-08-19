/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/19 21:24:23 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>

enum	e_token_type
{
	WORD = 100,
	NEWLINE,
	AND_IF,
	OR_IF,
	PIPE,
	SEMI,
	RED_IN,
	RED_OUT,
	HERE_DOC,
	RED_APD_OUT,
	PARENTHESES
};

typedef struct s_lx_token
{
	char				*startpoint;
	int					token_type;
	char				interpret_symbol;
	char				*interpreted_str;
	struct s_lx_token	*next;
}	t_lx_token;
#endif