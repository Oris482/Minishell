/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:25:42 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/13 14:54:39 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dic	*make_envp_node(char *name, char *value, t_dic *next, t_dic *prev)
{
	t_dic	*new;

	new = (t_dic *)my_calloc(1, sizeof(t_dic));
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

	i = 0;
	category = 'A';
	while (i < DIC_MAX)
	{
		category += 4 * (category == 'Z' + 1) + (category == '_' + 1);
		g_dic[i].value = ft_chr_to_str(category++);
		g_dic[i].prev = &g_dic[i];
		i++;
	}
}

void	ft_lstadd_last(t_dic *head, t_dic *new)
{
	t_dic *const last = get_last_dic(head);

	head->prev = new;
	last->next = new;
	new->prev = last;
}

void	ft_lstadd_next(t_dic *cur, t_dic *new)
{
	if (cur == get_last_dic(cur))
		return ft_lstadd_last(get_first_dic(cur), new);
	new->next = cur->next;
	cur->next = new;
	new->prev = cur;
}

int	comapre_order_dic(const t_dic *next, const t_dic *new)
{
	int i;
	const char *s1;
	const char *s2;

	i = 0;
	if (!next)
		return (GREATER_THAN);
	s1 = next->name;
	s2 = new->name;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// int	comapre_order_word(const char *s1, const char *s2)
// {
//     int i;
//
//     i = 0;
//     if (!s1)
//         return (GREATER_THAN);
//     while (s1[i] && s2[i] && s1[i] == s2[i])
//         i++;
//     return (s1[i] - s2[i]);
// }
/*	AA AB AC	AA	AAB => 음수
 *				AAA AAB => 음수
 *	AAB			AB	AAB => 양수
 */

void	ft_lstadd_order(t_dic *head, t_dic *new)
{
	int		old_val;
	int		val;
	t_dic	*cur;

	if (!head)
		return ;
	cur = head;
	old_val = LESS_THAN;
	while (cur)
	{
		val = comapre_order_word(cur->next, new);
		if (old_val < 0 && val > 0)
			return ft_lstadd_next(cur, new);
		old_val = val;
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
// 'A' 0
// 'Z' 25
// '_' 26
// 'a' 27

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
		ft_lstadd_order(&g_dic[idx], make_envp_node(ft_strcpy(envp[j], pos), \
											ft_strdup(pos + 1), NULL, NULL));
		j++;
	}
	print_dictionary_lst();
}
