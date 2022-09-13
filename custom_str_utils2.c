/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:04:59 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/11 19:02:59 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(const char *start, const char *end)
{
	char	*ret;
	size_t	len;
	int		idx;

	len = end - start;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		exit(GENERAL_EXIT_CODE);
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
