/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/04 20:33:47 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

static void	_minishell_routine(t_lx_token *token_list)
{
	t_lx_token	*cur_node;
	t_lx_token	*new_head;

	cur_node = token_list->next->next->next->next->next;
	print_token_list(token_list);
	print_token_next(token_list);
	print_token_prev(token_list);
	check_syntax_error(token_list);

	// printf("CUTTING\n");
	// printf("cur_node_token_str = %s\n", cur_node->token_str);
	// new_head = cut_front_node(cur_node);
	// print_token_next(new_head);
	// print_token_prev(new_head);
	// print_token_next(cur_node);
	// print_token_prev(cur_node);

	printf("POPPING\n");
	printf("cur_node_token_str = %s\n", cur_node->token_str);
	new_head = pop_node(&token_list, cur_node, cur_node->next);
	print_token_next(new_head);
	print_token_prev(new_head);
	print_token_next(token_list);
	print_token_prev(token_list);
	
	
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_lx_token		*token_list;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	while (true)
	{
		token_list = NULL;
		full_line = line_handler(&oflag);
		if (full_line && *full_line != '\0')
			add_history(full_line);
		if (!oflag.quote && !oflag.parentheses)
		{
			if (lexer(&token_list, full_line, envp) == ERROR)
				return (1);
			_minishell_routine(token_list);
		}
		my_multi_free(full_line, token_list, NULL, NULL);
	}
	(void)argc;
	(void)argv;
	return (0);
}
