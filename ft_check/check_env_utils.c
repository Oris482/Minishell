/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:56:31 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 02:27:36 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_number_chr(int c)
{
	return ('0' <= c && c <= '9');
}

int	is_upper_alpha_chr(int c)
{
	return ('A' <= c && c <= 'Z');
}

int	is_lower_alpha_chr(int c)
{
	return ('a' <= c && c <= 'z');
}

int	is_dict_chr(int c)
{
	return (is_upper_alpha_chr(c) || is_lower_alpha_chr(c) || c == '_');
}

int	is_env_chr(int c, int idx)
{
	if (idx == 0)
		return (is_dict_chr(c));
	return (is_number_chr(c) || is_dict_chr(c));
}
