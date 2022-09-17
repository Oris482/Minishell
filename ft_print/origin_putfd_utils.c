/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   origin_putfd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:45:47 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/17 22:17:51 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_print.h"

void	ft_putchar_fd(const char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putendl_fd(const char *s, int fd)
{
	if (fd >= 0 && s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
