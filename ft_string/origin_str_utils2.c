/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   origin_str_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:05:40 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/26 20:50:31 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_string.h"
#include "ft_alloc.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (s1[idx] && s2[idx])
	{
		if (s1[idx] != s2[idx])
			return (FALSE);
		idx++;
	}
	if (s1[idx] || s2[idx])
		return (FALSE);
	return (SUCCESS);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	dup = (char *)my_malloc(size * sizeof(char));
	ft_strlcpy(dup, s, size);
	return (dup);
}
