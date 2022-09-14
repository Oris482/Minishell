/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:59:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/14 22:09:52 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../minishell.h"

char	*my_getenv(const char *name)
{
	int		idx;
	t_dict	*find_node;

	idx = chr_to_idx(*name);
	find_node = find_dict(g_dict[idx].next, name);
	if (!find_node)
		return (NULL);
	return (find_node->value);
}
