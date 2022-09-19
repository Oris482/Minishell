/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:11:18 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/19 22:55:57 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_environ.h"
#include "ft_check.h"

t_dict	*get_last_dict(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->next)
		dict = dict->prev;
	return (dict);
}

t_dict	*get_first_dict(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->prev->next)
		dict = dict->prev;
	return (dict);
}

int	check_match_word(const char *word1, const char *word2)
{
	int	i;

	if (!word1 || !word2)
		return (FALSE);
	i = -1;
	while (++i + 1 && (word1[i] || word2[i]))
		if (word1[i] != word2[i])
			return (FALSE);
	return (TRUE);
}

int	chr_to_dict_idx(char c)
{
	if (is_upper_alpha_chr(c))
		return (c - 'A' + 0);
	else if (c == '_')
		return (c - '_' + 26);
	else if (is_lower_alpha_chr(c))
		return (c - 'a' + 27);
	return (ERROR);
}

int	check_valid_env_name(char *name)
{
	int		i;

	if (!name)
		return (FALSE);
	i = -1;
	while (name[++i])
		if (is_env_chr(name[i], i) == FALSE)
			return (FALSE);
	return (TRUE);
}
