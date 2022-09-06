/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:34:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/06 20:54:26 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
// #include "minishell.h"

#include "./parser.h"
#include "../minishell.h"
#include "../lexer/lexer.h"

/*
 * is_xx 함수 계열 프로토타입int 따라감
 */
unsigned char	is_tree_and_or(int token_type)
{
	if (token_type == AND_IF)
		return (TREE_AND);
	else if (token_type == OR_IF)
		return (TREE_OR);
	return (TREE_UNDEFINED);
}

unsigned char	is_tree_pipe(int token_type)
{
	if (token_type == PIPE)
		return (TREE_PIPE);
	return (TREE_CMD);
}
