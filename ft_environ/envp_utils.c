/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:25:42 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:47:02 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_environ.h"
#include "ft_alloc.h"

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

int check_vaild_env_name(char *name)
{
	if (!name)
		return (FALSE);
	while (*name)
	{
		if (chr_to_idx(*name) < 0)
			return (FALSE);
		name++;
	}
	return (TRUE);
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

void	dict_lstadd_last(t_dict *head, t_dict *new)
{
	t_dict *const last = get_last_dict(head);

	head->prev = new;
	last->next = new;
	new->prev = last;
}

void	dict_lstadd_next(t_dict *cur, t_dict *new)
{
	if (cur == get_last_dict(cur))
		return dict_lstadd_last(get_first_dict(cur), new);
	new->prev = cur;
	new->next = cur->next;
	cur->next->prev = new;
	cur->next = new;

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

int	chr_to_idx(char c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A' + 0);
	else if (c == '_')
		return (c - '_' + 26);
	else if ('a' <= c && c <= 'z')
		return (c - 'a' + 27);
	return (ERROR);
}

void	envp_to_dict(char *envp[])
{
	int		j;

	setting_dictionary();
	j = 0;
	while (envp[j])
		add_dict(NULL, NULL, envp[j++]);
}

char 	**dict_to_envp(void)
{
	int			idx;
	int			cnt;
	t_dict		*cur;
	int			j;
	char		**new_envp;

	cnt = count_dict();
	new_envp = (char **)my_calloc(cnt + 1, sizeof(char *));
	j = 0;
	idx = 0;
	while (idx < DICT_MAX)
	{
		cur = g_dict[idx++].next;
		while (cur)
		{
			new_envp[j++] = ft_strsjoin(cur->name, "=", cur->value);
			cur = cur->next;
		}
	}
	return (new_envp);
}

