/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:25:42 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:26:07 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

int print_dictionary_lst()
{
	int	i;
	int	total = 0;
	t_dict	*cur;

	i = 0;
	while (i < DICT_MAX)
	{
		printf("category : %s\n", g_dict[i].value);
		cur = g_dict[i].next;
		while (cur)
		{
			printf("L %s=%s\n", cur->name, cur->value);
			total++;
			cur = cur->next;
		}
		i++;
	}
	return (total);
}

int	print_strs(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i])
		printf("%s\n", strs[i++]);
	return (i);
}
