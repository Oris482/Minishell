/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/31 18:12:05 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "myfunc.h"

void	*my_malloc(unsigned int size)
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

void	*my_calloc(unsigned int size)
{
	char	*pointer;
	size_t	idx;

	pointer = (char *)my_malloc(size);
	idx = 0;
	while (idx < size)
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
