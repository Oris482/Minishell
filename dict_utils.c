/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:51:24 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/14 22:52:33 by minsuki2         ###   ########.fr       */
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

t_dict	*find_dict(t_dict *cur, const char *name)
{
	while (cur)
	{
		if (check_match_word(cur->name, name) == TRUE)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	erase_dict(char *name)
{
	int		idx;
	t_dict	*last_node;
	t_dict	*find_node;

	if (!name)
		return ;
	idx = chr_to_idx(*name);
	find_node = find_dict(&g_dict[idx], name);
	if (!find_node)
		return ;
	find_node->prev->next = find_node->next;
	if (find_node->next)
		find_node->next->prev = find_node->prev;
	last_node = g_dict[idx].prev;
	if (find_node == last_node)
		g_dict[idx].prev = find_node->prev;
	my_multi_free(find_node->name, find_node->value, find_node, NULL);
}

void add_dict(char *name, char *value, char *merge_str)
{
	int			idx;
	char		*pos;

	if ((!name && !value && !merge_str) \
		|| (merge_str && (name || value)) \
		|| (!name && value))
		return ;
	if (merge_str)
	{
		idx = chr_to_idx(*merge_str);
		pos = ft_strchr_null(merge_str, '=');
		name = ft_strcpy(merge_str, pos);
		value = ft_strdup(pos + 1);
	}
	else
		idx = chr_to_idx(*name);
	dict_lstadd_order(&g_dict[idx], make_envp_node(name, value, NULL, NULL));
}

void put_dict(char *name, char *value)
{
	if (!name)
		return ;
	erase_dict(name);
	add_dict(name, value, NULL);
}
