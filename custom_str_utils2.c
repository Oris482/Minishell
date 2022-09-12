/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:33:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/12 01:38:36 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp_ignore_capital(char *ref, char *target)
{
    unsigned char   c;

    if (!ref || !target)
        return (FALSE);
    while (*ref && *target)
	{
        c = *target;
        if (c >= 'A' && c <= 'Z')
            c += 32;
		if (*ref != c)
			return (FALSE);
		ref++;
		target++;
	}
	return (SUCCESS);
}
