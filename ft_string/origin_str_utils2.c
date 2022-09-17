/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   origin_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:05:40 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
		*((unsigned char *)b + len) = (unsigned char)c;
	return (b);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (FALSE);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (FALSE);
	return (SUCCESS);
}

char	*ft_itoa(int num)
{
	int		reverse_num;
	int		len;
	int		idx;
	int		sign;
	char	*ret;

	reverse_num = 0;
	len = 0;
	idx = 0;
	sign = 0;
	if (num <= 0)
		len++;
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	while (num > 0)
	{
		reverse_num = (reverse_num << 3) + (reverse_num << 1) + (num % 10);
		num /= 10;
		len++;
	}
	ret = (char *)my_calloc(1, len + 1);
	if (sign)
	{
		ret[idx++] = '-';
		len--;
	}
	while (len-- > 0)
	{
		ret[idx++] = (reverse_num % 10) + '0';
		reverse_num /= 10;
	}
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + 1;
	dup = (char *)my_malloc(size * sizeof(char));
	ft_strlcpy(dup, s1, size);
	return (dup);
}
