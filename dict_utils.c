/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:51:24 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/14 21:10:09 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_match_word(const char *word1, const char *word2)
{
	int	i;

	if (!word1 || !word2)
		return (FALSE);
	i = -1;
	while (++i + 1 && (word1[i] || word2[i]))
		if (word1[i] != word2[i])
			return (FALSE);
	return (TRUE);
}

t_dict	*find_env_dict(t_dict *cur, const char *name)
{
	while (cur)
	{
		if (check_match_word(cur->name, name) == TRUE)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/* Please never NULL */
void	erase_dict(char *name)
{
	int				idx = chr_to_idx(*name);
	t_dict *const	head_node = &g_dict[idx];
	t_dict *const	last_node = head_node->prev;
	t_dict			*find_node;

	find_node = find_env_dict(&g_dict[idx], name);
	if (!find_node)
		return ;
	find_node->prev->next = find_node->next;
	if (find_node->next)
		find_node->next->prev = find_node->prev;
	if (find_node == last_node)
		head_node->prev = find_node->prev;
	my_multi_free(find_node->name, find_node->value, find_node, NULL);
}

/* Please never NULL */
void add_dict(char *merge_str)
{
	const int	idx = chr_to_idx(*merge_str);
	char		*pos;

	pos = ft_strchr_null(merge_str, '=');
	dict_lstadd_order(&g_dict[idx], make_envp_node(ft_strcpy(merge_str, pos), \
											ft_strdup(pos + 1), NULL, NULL));
}
