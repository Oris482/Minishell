/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 21:43:20 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_environ.h"

t_dict	*get_last_dict(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->next)
		dict = dict->prev;
	return (dict);
}

t_dict	*get_first_dict(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->prev->next)
		dict = dict->prev;
	return (dict);
}
