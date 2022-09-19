/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:22:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/20 01:38:49 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"
#include "ft_print.h"
#include "ft_string.h"
#include "ft_check.h"
#include "ft_alloc.h"

void	_set_heredoc_info(t_heredoc_info *heredoc_info, char *pure_limiter)
{
	heredoc_info->limiter = ft_strdup("");
	if (ft_strchr(pure_limiter, '\"') || ft_strchr(pure_limiter, '\''))
		heredoc_info->option = DO_NOT_TRANSLATE;
	else
		heredoc_info->option = TRANSLATE_ENV;
	while (*pure_limiter)
	{
		if (!is_quote(*pure_limiter))
		{
			ft_strjoin_self_add_free(&heredoc_info->limiter, \
										ft_chr_to_str(*pure_limiter));
		}
		pure_limiter++;
	}
}

int	make_tmp_heredoc(t_lx_token *token, char *pure_limiter)
{
	int				write_fd;
	pid_t			pid;
	int				status;
	char			*tmpname;
	t_heredoc_info	heredoc_info;

	_set_heredoc_info(&heredoc_info, pure_limiter);
	if (make_tmpfile(&tmpname, &write_fd) == FALSE)
	{
		my_free(heredoc_info.limiter);
		return (handle_redirections_error("Here-doc", NULL));
	}
	token->interpreted_str = tmpname;
	signal(SIGINT, SIG_IGN);
	pid = my_fork();
	if (pid == CHILD_PID)
		write_tmp_heredoc(&heredoc_info, write_fd);
	waitpid(pid, &status, WUNTRACED);
	set_init_signal();
	close(write_fd);
	my_free(heredoc_info.limiter);
	return (WEXITSTATUS(status));
}

int	redi_heredoc(char *filename)
{
	int	read_fd;

	read_fd = open(filename, O_RDONLY);
	if (read_fd == ERROR)
		return (print_error_str("here-doc", NULL, \
					"can't open tmp file", GENERAL_EXIT_CODE));
	my_dup2(read_fd, STDIN_FILENO);
	close(read_fd);
	return (SUCCESS_EXIT_CODE);
}
