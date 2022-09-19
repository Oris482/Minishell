/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:26:11 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 23:32:37 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"
#include "ft_string.h"
#include "ft_alloc.h"
#include "ft_environ.h"

static char	*_make_tmpname(char *ref, char *prefix)
{
	struct stat	buf;
	char		*filename;
	int			i;
	char		*i_str;

	if (ref == NULL)
		ft_strjoin_self(&ref, "/tmp/");
	ft_strjoin_self(&ref, prefix);
	i = -1;
	while (++i < 4242)
	{
		i_str = ft_itoa(i);
		filename = ft_strsjoin(ref, i_str, NULL);
		my_free(i_str);
		stat(filename, &buf);
		if (errno == ENOENT)
		{
			errno = 0;
			my_free(ref);
			return (filename);
		}
		my_free(filename);
	}
	my_free(ref);
	return (NULL);
}

int	make_tmpfile(char **tmpname, int *fd)
{
	*tmpname = _make_tmpname(ft_strdup(my_getenv("TMPDIR")), "minishell_");
	if (*tmpname == NULL)
		return (FALSE);
	*fd = open(*tmpname, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (*fd == ERROR)
		return (FALSE);
	return (SUCCESS);
}

static void	_heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(SIG_DEFAULT_EXIT_CODE + SIGINT);
	}
}

static void	_heredoc_signal_handler(void)
{
	signal(SIGINT, _heredoc_sigint_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	write_tmp_heredoc(char *limiter, int write_fd)
{
	char	*line;

	_heredoc_signal_handler();
	line = my_readline("> ");
	while (line && !ft_strcmp(line, limiter))
	{
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		my_free(line);
		line = my_readline("> ");
	}
	my_free(line);
	close(write_fd);
	exit(SUCCESS_EXIT_CODE);
}
