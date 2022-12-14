/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_library.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:27:23 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/18 06:52:26 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBRARY_H
# define FT_LIBRARY_H

# include <unistd.h>
# include <limits.h>

int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_itoa(int n);
#endif
