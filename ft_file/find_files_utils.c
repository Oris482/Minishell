/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:54:23 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 20:45:29 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "lexer.h"

char	*path_plus_filename(char *pwd, t_file *files, int idx, int dir_flag)
{
	if (dir_flag)
		return (ft_strsjoin(pwd, files[idx].name, "/"));
	else
		return (ft_strsjoin(pwd, files[idx].name, NULL));
}

int	get_target_level(char **splited)
{
	int	idx;

	idx = 0;
	while (splited[idx])
		idx++;
	return (idx - 1);
}
