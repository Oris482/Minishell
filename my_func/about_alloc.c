/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/30 22:48:47 by jaesjeon         ###   ########.fr       */
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
	void	*pointer;
	size_t	idx;

	pointer = my_malloc(size);
	idx = 0;
	while (idx < size)
		pointer[idx++] = 0;
	return (pointer);
}

void	my_free(void *ptr)
{
	if (ptr)
		free(ptr);
}
