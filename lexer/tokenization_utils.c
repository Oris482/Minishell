/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:15:19 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/07 20:33:48 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote_flag(const char c, int *quote_flag)
{
	if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
		*quote_flag ^= QUOTE;
	else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
		*quote_flag ^= DQUOTE;
}

// void	set_quote_flag(const char c, unsigned char *quote_flag)
// {
//     if (c == '\'' && (!*quote_flag || *quote_flag == QUOTE))
//         *quote_flag ^= QUOTE;
//     else if (c == '\"' && (!*quote_flag || *quote_flag == DQUOTE))
//         *quote_flag ^= DQUOTE;
// }

void	set_parentheses_flag(const char c, int *parentheses_flag, \
								int *quote_flag)
{
	if (!*quote_flag)
	{
		if (c == '(' && !*parentheses_flag)
			*parentheses_flag ^= PARENTHESES_OPEN;
		else if (c == ')')
			if (*parentheses_flag == PARENTHESES_OPEN)
				*parentheses_flag ^= PARENTHESES_OPEN;
	}
}

// void	set_parentheses_flag(const char c, unsigned char *parentheses_flag, \
//                                 unsigned char *quote_flag)
// {
//     if (!*quote_flag)
//     {
//         if (c == '(' && !*parentheses_flag)
//             *parentheses_flag ^= PARENTHESES_OPEN;
//         else if (c == ')')
//             if (*parentheses_flag == PARENTHESES_OPEN)
//                 *parentheses_flag ^= PARENTHESES_OPEN;
//     }
// }

void	set_token_type(t_lx_token *token_node, char c)
{
	if (token_node->token_type == UNDEFINED)
	{
		token_node->token_type = is_token_seperator(c);
		if (token_node->token_type == UNDEFINED)
			token_node->token_type = WORD;
	}
}

void	set_interpret_symbol(t_lx_token *token_node, char c, \
								int *quote_flag)
{
	if (is_quote(c) == *quote_flag)
		token_node->interpret_symbol |= *quote_flag;
	if (!*quote_flag || *quote_flag == DQUOTE)
		token_node->interpret_symbol |= is_dollar(c);
	if (!*quote_flag)
		token_node->interpret_symbol |= is_wildcard(c);
	if (!*quote_flag)
		token_node->interpret_symbol |= is_tilde(c);
}

// void	set_interpret_symbol(t_lx_token *token_node, char c, \
//                                 unsigned char *quote_flag)
// {
//     if (is_quote(c) == *quote_flag)
//         token_node->interpret_symbol |= *quote_flag;
//     if (!*quote_flag || *quote_flag == DQUOTE)
//         token_node->interpret_symbol |= is_dollar(c);
//     if (!*quote_flag)
//         token_node->interpret_symbol |= is_wildcard(c);
//     if (!*quote_flag)
//         token_node->interpret_symbol |= is_tilde(c);
// }
