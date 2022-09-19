/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:48:04 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 22:45:58 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_alloc.h"
#include "ft_tree.h"

static void	_linked_lst_fclean(t_lx_token *cur_list)
{
	t_lx_token	*tmp;

	while (cur_list)
	{
		if (cur_list->token_type == HERE_DOC \
								&& cur_list->interpreted_str != NULL)
			unlink(cur_list->interpreted_str);
		my_multi_free(cur_list->token_str, cur_list->interpreted_str, \
															NULL, NULL);
		tmp = cur_list;
		cur_list = cur_list->next;
		my_free(tmp);
	}
}

static void	_tree_node_free(t_tree *cur_tree)
{
	_linked_lst_fclean(cur_tree->token_data);
	my_free(cur_tree);
}

void	*list_tree_free(t_lx_token *list, t_tree *tree)
{
	_linked_lst_fclean(list);
	tree_traversal(tree, TREE_ALL, _tree_node_free);
	return (NULL);
}

void	char_dimen2_free(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		my_free(strs[i++]);
	my_free(strs);
}

void	files_free(t_file *files)
{
	int	i;

	i = -1;
	while (++i < files->n)
		my_free(files[i].name);
	my_free(files);
}
