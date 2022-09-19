/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:33:30 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 03:52:52 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_string.h"
#include "ft_alloc.h"

int	ft_strcmp_ignore_capital(const char *ref, const char *target)
{
	unsigned char	c;
	int				idx;

	idx = 0;
	if (!ref || !target)
		return (FALSE);
	while (ref[idx] && target[idx])
	{
		c = target[idx];
		if (c >= 'A' && c <= 'Z')
			c += 32;
		if (ref[idx] != c)
			return (FALSE);
		idx++;
	}
	if (ref[idx] || target[idx])
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

char	*ft_strjoin_myself_free(char **str, char *add)
{
	ft_strjoin_self(str, add);
	my_free(add);
	return (*str);
}
