/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:23:44 by minsuki2          #+#    #+#             */
/*   Updated: 2022/08/25 21:47:24 by minsuki2         ###   ########.fr       */
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

void	my_free(void *ptr)
{
	free(ptr);
}
