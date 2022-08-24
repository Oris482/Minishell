/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/24 21:12:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

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

void	my_free(void *ptr)
{
	free(ptr);
}
