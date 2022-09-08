/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:00:34 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/08 17:49:31 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myfunc.h"
#include "liner.h"
#include "lexer.h"
#include "parser.h"

// void my_tree_free(t_tree *cur_tree)
// {
//     if (!cur_tree)
//         return ;
//     my_tree_free(cur_tree->left);
//     my_tree_free(cur_tree->right);
//     lst_fclean(cur_tree->token_data);
//     free(cur_tree);
// }



static void	_minishell_routine(char *full_line, t_oflag *oflag)
{
	t_lx_token		*token_list;
	t_tree			*root_tree;


	token_list = lexer(full_line, oflag);
	if (token_list == NULL)
		return ;
	print_token_list(token_list);
	print_token_next(token_list);
	print_token_prev(token_list);
	if (parser(&root_tree, token_list) == ERROR)
	{
		tree_traversal(root_tree, TREE_ALL, tree_free);
		return ;
	}
	printf("----------- < TREE > --------------\n\n");
	print_ascii_tree(root_tree);
	tree_traversal(root_tree, TREE_ALL, tree_free);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*full_line;
	t_oflag			oflag;

	signal_handler();
	terminal_off_control_chars();
	(void)envp;
	// ft_str_array_dup envp 할당
	while (true)
	{
		full_line = liner(&oflag);
		system("leaks -q minishell");
		if (full_line && *full_line == '\0')
		{
			my_multi_free(full_line, NULL, NULL, NULL);
			continue ;
		}
		add_history(full_line);
		if (!oflag.quote && !oflag.parentheses)
			_minishell_routine(full_line, &oflag);
		my_multi_free(full_line, NULL, NULL, NULL);
		system("leaks -q minishell");
	}
	(void)argc;
	(void)argv;
	return (0);
}
