/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:59:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 22:57:32 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_environ.h"
#include "ft_check.h"
#include "ft_library.h"
#include "ft_alloc.h"
#include "ft_string.h"
#include "minishell_info.h"
#include "ft_environ.h"

char	*my_getenv(const char *name)
{
	int		idx;
	t_dict	*find_node;

	if (*name == '\0')
		return (NULL);
	idx = chr_to_dict_idx(*name);
	find_node = find_dict(g_dict[idx].next, name);
	if (!find_node)
		return (NULL);
	return (find_node->value);
}

char	**dict_to_envp(void)
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

static void	_setting_dictionary(void)
{
	int		i;
	char	category;

	category = 'A';
	i = 0;
	while (i < DICT_MAX)
	{
		category += 4 * (category == 'Z' + 1) + (category == '_' + 1);
		g_dict[i].value = ft_chr_to_str(category++);
		g_dict[i].prev = &g_dict[i];
		i++;
	}
}

void	envp_to_dict(char *envp[])
{
	int		j;
	char	*cur_shlvl;

	_setting_dictionary();
	j = 0;
	while (envp[j])
		add_dict(NULL, NULL, envp[j++]);
	put_dict(ft_strdup("OLDPWD"), ft_strdup(""));
	erase_dict("_");
	cur_shlvl = my_getenv("SHLVL");
	if (cur_shlvl == NULL)
		put_dict(ft_strdup("SHLVL"), ft_strdup("1"));
	else
		put_dict(ft_strdup("SHLVL"), ft_itoa(ft_atoi(cur_shlvl) + 1));
}
