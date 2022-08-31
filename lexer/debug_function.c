/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:23:45 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/08/31 16:28:58 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_lx_token *token_list)
{
	char	*token_type;

	while (token_list)
	{
		if (token_list->token_type == WORD)
			token_type = "WORD";
		else if (token_list->token_type == NEW_LINE)
			token_type = "NEW_LINE";
		else if (token_list->token_type == AND_IF)
			token_type = "AND_IF";
		else if (token_list->token_type == OR_IF)
			token_type = "OR_IF";
		else if (token_list->token_type == PIPE)
			token_type = "PIPE";
		else if (token_list->token_type == RED_IN)
			token_type = "RED_IN";
		else if (token_list->token_type == RED_OUT)
			token_type = "RED_OUT";
		else if (token_list->token_type == HERE_DOC)
			token_type = "HERE_DOC";
		else if (token_list->token_type == RED_APD_OUT)
			token_type = "RED_APD_OUT";
		else if (token_list->token_type == PARENTHESES_OPEN)
			token_type = "PARENTHESES_OPEN";
		else if (token_list->token_type == PARENTHESES_CLOSE)
			token_type = "PARENTHESES_CLOSE";
		else if (token_list->token_type == SPACE_SET)
			token_type = "SPACE_SET";
		printf("token_str = [%s]\n", token_list->token_str);
		printf("token_type = %s(%d) interpret_symbol = %d\n", token_type, \
				token_list->token_type, token_list->interpret_symbol);
		printf("interpret_str = [%s]\n\n", token_list->interpreted_str);
		token_list = token_list->next;
	}
}

void	classify(struct dirent *ent)
{
	printf("%s\t\t", ent->d_name);
	if (ent->d_type == DT_BLK)
		printf("Block Device\n");
	else if (ent->d_type == DT_CHR)
		printf("Character Device\n");
	else if (ent->d_type == DT_DIR)
		printf("Directory\n");
	else if (ent->d_type == DT_LNK)
		printf("Symbolic Link\n");
	else if (ent->d_type == DT_REG)
		printf("Regular File\n");
	else if (ent->d_type == DT_SOCK)
		printf("Unix Domain Socket\n");
	else
		printf("Unknown Type File\n");
}