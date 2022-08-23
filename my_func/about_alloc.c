/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_stdlib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/23 11:29:59 by minsuki2         ###   ########.fr       */
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
		exit(1);
	}
	return (pointer);
}

void	my_free(void *ptr)
{
	free(ptr);
}
