/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:23:03 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/18 06:57:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_library.h"
#include "ft_alloc.h"

static void	_itoa_nbr(int n, char *dst, size_t len)
{
	if (n > -10 && n < 10)
	{
		if (n < 0)
		{
			dst[0] = '-';
			n *= -1;
		}
		dst[len - 1] = n % 10 + '0';
		return ;
	}
	_itoa_nbr(n / 10, dst, len - 1);
	if (n >= 0)
		dst[len - 1] = n % 10 + '0';
	else
		dst[len - 1] = -(n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	cnt;
	int		tmp;

	cnt = 1;
	tmp = n;
	while (tmp && cnt++)
		tmp /= 10;
	if (n > 0)
		cnt--;
	ptr = (char *)my_malloc(sizeof(char) * (cnt + 1));
	ptr[cnt] = '\0';
	_itoa_nbr(n, ptr, cnt);
	return (ptr);
}

