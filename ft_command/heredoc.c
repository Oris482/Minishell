/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:22:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/19 20:47:05 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"
#include "ft_print.h"

int	make_tmp_heredoc(t_lx_token *token, char *limiter)
{
	int		write_fd;
	pid_t	pid;
	int		status;
	char	*tmpname;

	if (make_tmpfile(&tmpname, &write_fd) == FALSE)
		return (handle_redirections_error("Here-doc", NULL));
	token->interpreted_str = tmpname;
	signal(SIGINT, SIG_IGN);
	pid = my_fork();
	if (pid == CHILD_PID)
		write_tmp_heredoc(limiter, write_fd);
	waitpid(pid, &status, WUNTRACED);
	set_init_signal();
	close(write_fd);
	return (SUCCESS_EXIT_CODE);
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
