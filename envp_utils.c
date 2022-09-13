/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:25:42 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/13 23:02:21 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*make_envp_node(char *name, char *value, t_dict *next, t_dict *prev)
{
	t_dict	*new;

	new = (t_dict *)my_calloc(1, sizeof(t_dict));
	new->name = name;
	new->value = value;
	new->next = next;
	new->prev = prev;
	return (new);
}

void	setting_dictionary(void)
{
	int		i;
	char	category;

	category = 'A';
	i = 0;
	while (i < DICT_MAX)
	{
		// debug
		category += 4 * (category == 'Z' + 1) + (category == '_' + 1);
		g_dict[i].value = ft_chr_to_str(category++);
		// debug
		g_dict[i].prev = &g_dict[i];
		i++;
	}
}

void	ft_lstadd_last(t_dict *head, t_dict *new)
{
	t_dict *const last = get_last_dict(head);

	head->prev = new;
	last->next = new;
	new->prev = last;
}

void	ft_lstadd_next(t_dict *cur, t_dict *new)
{
	if (cur == get_last_dict(cur))
		return ft_lstadd_last(get_first_dict(cur), new);
	new->next = cur->next;
	cur->next = new;
	new->prev = cur;
}

int	comapre_order_dict(const t_dict *next, const t_dict *new)
{
	int i;
	const char *s1;
	const char *s2;

	if (!next)
		return (GREATER_THAN);
	s1 = next->name;
	s2 = new->name;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_lstadd_order(t_dict *head, t_dict *new)
{
	int		val;
	t_dict	*cur;

	if (!head)
		return ;
	cur = head;
	while (cur)
	{
		val = comapre_order_dict(cur->next, new);
		if (val > 0)
			return ft_lstadd_next(cur, new);
		cur = cur->next;
	}
}

int	chr_to_idx(char c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A' + 0);
	else if ('a' <= c && c <= 'z')
		return (c - 'a' + 27);
	return (c - '_' + 26);
}

void	char_dimen2_to_lst(char *envp[])
{
	int		idx;
	int		j;
	char	*pos;

	print_envp(envp);
	setting_dictionary();
	j = 0;
	while (envp[j])
	{
		pos = ft_strchr_null(envp[j], '=');
		idx = chr_to_idx(*envp[j]);
		ft_lstadd_order(&g_dict[idx], make_envp_node(ft_strcpy(envp[j], pos), \
											ft_strdup(pos + 1), NULL, NULL));
		j++;
	}
	print_dictionary_lst();
}


