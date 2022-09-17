/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:59:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

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
