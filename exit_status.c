/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:34:06 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/11 20:40:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	*_get_address_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	set_exit_status(int status)
{
	int	*exit_status;

	exit_status = _get_address_exit_status();
	*exit_status = status;
	return ;
}

int	get_exit_status(void)
{
	int	*exit_status;

	exit_status = _get_address_exit_status();
	return (*exit_status);
}
