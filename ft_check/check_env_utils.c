/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:56:31 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/18 05:03:39 by minsuki2         ###   ########.fr       */
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

int is_env_chr(char *head, char *cur)
{
	if (!head || !cur)
		return (0);
	if (head == cur)
		return (is_dict_chr(*cur));
	return (is_number_chr(*cur) || is_dict_chr(*cur));
}
