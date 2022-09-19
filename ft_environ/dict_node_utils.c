/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:44:25 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 22:57:48 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

int	comapre_order_dict(const t_dict *next, const t_dict *new)
{
	int			i;
	const char	*s1;
	const char	*s2;

	if (!next)
		return (GREATER_THAN);
	s1 = next->name;
	s2 = new->name;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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

static void	_dict_lstadd_last(t_dict *head, t_dict *new)
{
	t_dict *const	last = get_last_dict(head);

	head->prev = new;
	last->next = new;
	new->prev = last;
}

static void	_dict_lstadd_next(t_dict *cur, t_dict *new)
{
	if (cur == get_last_dict(cur))
		return (dict_lstadd_last(get_first_dict(cur), new));
	new->prev = cur;
	new->next = cur->next;
	cur->next->prev = new;
	cur->next = new;
}

void	dict_lstadd_order(t_dict *head, t_dict *new)
{
	int		val;
	t_dict	*cur;

	if (!head)
		return ;
	cur = head;
	val = LESS_THAN;
	while (cur && val < 0)
	{
		val = comapre_order_dict(cur->next, new);
		if (val > 0)
			dict_lstadd_next(cur, new);
		else if (val == 0)
			return ;
		cur = cur->next;
	}
}
