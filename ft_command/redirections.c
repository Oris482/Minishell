/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:50:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 20:45:09 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"
#include "ft_command.h"
#include "ft_string.h"
#include "ft_print.h"
#include "ft_alloc.h"
#include "ft_token.h"
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

static int	_make_tmpfile(char **tmpname, int *fd)
{
	*tmpname = _make_tmpname(ft_strdup(my_getenv("TMPDIR")), "minishell_");
	if (*tmpname == NULL)
		return (FALSE);
	*fd = open(*tmpname, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (*fd == ERROR)
		return (FALSE);
	return (SUCCESS);
}

int	handle_redirections_error(const char *cmd, const char *arg)
{
	if (errno == EACCES)
		return (print_error_str(cmd, arg, \
				"Permission denied", GENERAL_EXIT_CODE));
	else if (errno == EIO)
		return (print_error_str(cmd, arg, \
				"I/O error occurs", GENERAL_EXIT_CODE));
	else if (errno == EISDIR)
		return (print_error_str(cmd, arg, \
				"It is a directory", GENERAL_EXIT_CODE));
	else if (errno == EMFILE)
		return (print_error_str(cmd, arg, \
				"Reached limit for open fd", GENERAL_EXIT_CODE));
	else if (errno == ENAMETOOLONG)
		return (print_error_str(cmd, arg, \
				"File name is too long", GENERAL_EXIT_CODE));
	else if (errno == ENOENT)
		return (print_error_str(cmd, arg, \
				"No such file or directory", GENERAL_EXIT_CODE));
	else if (errno == ENOTDIR)
		return (print_error_str(cmd, arg, \
				"Not a directory", GENERAL_EXIT_CODE));
	else
		return (print_error_str(cmd, arg, NULL, GENERAL_EXIT_CODE));
}

void	heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(SIG_DEFAULT_EXIT_CODE + SIGINT);
	}
}

void	heredoc_signal_handler(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	write_tmp_heredoc(char *limiter, int write_fd)
{
	char	*line;

	heredoc_signal_handler();
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

int	make_tmp_heredoc(t_lx_token *token, char *limiter)
{
	int		write_fd;
	pid_t	pid;
	int		status;
	char	*tmpname;

	if (_make_tmpfile(&tmpname, &write_fd) == FALSE)
		return (handle_redirections_error("Here-doc", NULL));
	token->interpreted_str = tmpname;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
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
		return (print_error_str("here-doc", NULL, "can't open tmp file", GENERAL_EXIT_CODE));
	if (dup2(read_fd, STDIN_FILENO) == ERROR)
		return (print_error_str("here-doc", NULL, NULL, GENERAL_EXIT_CODE));
	close(read_fd);
	return (SUCCESS_EXIT_CODE);
}

int	redi_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return (handle_redirections_error("Redi-in", filename));
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		close(fd);
		return (print_error_str("Redi-in", NULL, NULL, GENERAL_EXIT_CODE));
	}
	close(fd);
	return (SUCCESS_EXIT_CODE);
}

int	redi_out(char *filename, int extra_mode)
{
	const int	open_mode = O_WRONLY | O_CREAT | extra_mode;
	const int	file_modes = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int			fd;

	fd = open(filename, open_mode, file_modes);
	if (fd == ERROR)
		return (handle_redirections_error("Redi-out", filename));
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		close(fd);
		return (print_error_str("redi-out", NULL, NULL, GENERAL_EXIT_CODE));
	}
	close(fd);
	return (SUCCESS_EXIT_CODE);
}

int	redi_middleware(t_lx_token *token)
{
	int	exit_code;

	exit_code = SUCCESS_EXIT_CODE;
	while (token)
	{
		if (token->token_type == RED_IN)
			exit_code = redi_in(get_token_str(token->next));
		else if (token->token_type == RED_OUT)
			exit_code = redi_out(get_token_str(token->next), O_TRUNC);
		else if (token->token_type == RED_APD_OUT)
			exit_code = redi_out(get_token_str(token->next), O_APPEND);
		else if (token->token_type == HERE_DOC)
			exit_code = redi_heredoc(token->interpreted_str);
		else
			break ;
		if (exit_code != SUCCESS_EXIT_CODE)
			break ;
		token = token->next->next;
	}
	if (exit_code == SUCCESS_EXIT_CODE && token != NULL)
		return (print_error_str("Redirect", token->prev->token_str, \
								"ambigous redirect", GENERAL_EXIT_CODE));
	return (exit_code);
}
