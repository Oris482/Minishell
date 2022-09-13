/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:51:24 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/13 23:29:36 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*find_env_dict(t_dict *cur, const char *name)
{
	while (cur)
	{
		if (check_match_word(cur->name, name) == TRUE)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

// void erase_dict(char *name)
// {
//     t_dict	*find_node;
//
//     find_node = find_env_dict(g_dict[chr_to_idx(*name)], );
// }

// void add_dict(char *name, char *value)
// {
// }
