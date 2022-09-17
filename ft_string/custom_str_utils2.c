/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:33:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 22:18:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_string.h"
#include "ft_alloc.h"

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
    if (*ref || *target)
        return (FALSE);
	return (SUCCESS);
}

char	*ft_strcpy(const char *start, const char *end)
{
	char	*ret;
	size_t	len;
	int		idx;

	len = end - start;
	ret = (char *)my_malloc(len + 1);
	idx = 0;
	while (idx < (int)len)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

char	*ft_chr_to_str(char c)
{
	char	*str;

	str = (char *)my_malloc(2 * sizeof(char));
	str[1] = '\0';
	str[0] = c;
	return (str);
}
