/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 22:16:25 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_alloc.h"

void	*my_malloc(size_t size)
{
	void	*pointer;

	pointer = malloc(size);
	if (!pointer)
	{
		printf("%s\n", strerror(errno));
		exit(GENERAL_EXIT_CODE);
	}
	return (pointer);
}

void	*my_calloc(size_t count, size_t size)
{
	const size_t	full_size = count * size;
	char			*pointer;
	size_t			idx;

	pointer = (char *)my_malloc(full_size);
	idx = 0;
	while (idx < full_size)
		pointer[idx++] = 0;
	return ((void *)pointer);
}

void	my_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	my_multi_free(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	my_free(ptr1);
	my_free(ptr2);
	my_free(ptr3);
	my_free(ptr4);
}
