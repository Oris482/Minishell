/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:34:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/05 15:47:02 by minsuki2         ###   ########.fr       */
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
int		is_tree_and_or(int c)
{
	return (c == TREE_AND || c == TREE_OR);
}

int		is_tree_pipe(int c)
{
	return (c == TREE_PIPE);
}

int		is_tree_cmd(int c)
{
	return (c == TREE_CMD);
}
