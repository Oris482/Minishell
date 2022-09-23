/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:51:24 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/23 00:09:24 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_environ.h"
#include "ft_string.h"
#include "ft_alloc.h"

int	count_dict(t_dict dict[])
{
	int		idx;
	int		total;
	t_dict	*cur;

	idx = 0;
	total = 0;
	while (idx < DICT_MAX)
	{
		cur = dict[idx++].next;
		while (cur && ++total)
			cur = cur->next;
	}
	return (total);
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

t_dict	*add_dict(t_dict dict[], char *name, char *value, char *merge_str)
{
	int			idx;
	char		*pos;
	t_dict		*add_node;

	if ((!name && !value && !merge_str) \
		|| (merge_str && (name || value)) \
		|| (!name && value))
		return (NULL);
	if (merge_str)
	{
		idx = chr_to_dict_idx(*merge_str);
		pos = ft_strchr_null(merge_str + 1, '=');
		name = ft_strcpy(merge_str, pos);
		if (*pos)
			value = ft_strdup(pos + 1);
	}
	else
		idx = chr_to_dict_idx(*name);
	add_node = make_envp_node(name, value, NULL, NULL);
	dict_lstadd_order(&dict[idx], add_node);
	return (add_node);
}

t_dict	*put_dict(t_dict dict[], char *name, char *value)
{
	t_dict	*find_node;
	int		idx;

	if (!name)
		return (NULL);
	idx = chr_to_dict_idx(*name);
	find_node = find_dict(dict[idx].next, name);
	if (!find_node)
		return (add_dict(dict, name, value, NULL));
	else if (find_node && find_node->value && !value)
		my_multi_free(name, value, NULL, NULL);
	else
	{
		my_multi_free(name, find_node->value, NULL, NULL);
		find_node->value = value;
	}
	return (find_node);
}

void	erase_dict(t_dict dict[], char *name)
{
	int		idx;
	t_dict	*last_node;
	t_dict	*find_node;

	if (!name)
		return ;
	idx = chr_to_dict_idx(*name);
	find_node = find_dict(&dict[idx], name);
	if (!find_node)
		return ;
	find_node->prev->next = find_node->next;
	if (find_node->next)
		find_node->next->prev = find_node->prev;
	last_node = dict[idx].prev;
	if (find_node == last_node)
		dict[idx].prev = find_node->prev;
	my_multi_free(find_node->name, find_node->value, find_node, NULL);
}
