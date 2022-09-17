/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:50:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/17 21:23:18 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command.h"
#include "ft_string.h"
#include "ft_print.h"
#include "minishell.h"
#include "ft_free.h"
#include "ft_token.h"

static char	*_make_tmpname(char *prefix)
{
	struct stat	*buf;
	char		*ret;
	char		*suffix;
	int			i;

	ret = NULL;
	ft_strjoin_self(&ret, "/tmp/");
	ft_strjoin_self(&ret, prefix);
	suffix = "_j2m1";
	i = 0;
	while (i++ < 5)
	{
		stat(ret, buf);
		if (errno == ENOENT)
		{
			errno = 0;
			return (ret);
		}
		ft_strjoin_self(&ret, suffix);
	}
	return (NULL);
}

static int	_make_tmpfile(char **tmpname, int *fd)
{
	*tmpname = _make_tmpname("minishell");
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

int	redi_heredoc(char *limiter)
{
	int		fd[2];
	char	*tmpname;
	char	*line;

	if (_make_tmpfile(&tmpname, &fd[F_WRITE]) == FALSE)
		return (handle_redirections_error("Here-doc", NULL));
	line = my_readline("> ");
	while (line && !ft_strcmp(line, limiter))
	{
		my_free(line);
		write(fd[F_WRITE], line, ft_strlen(line));
		write(fd[F_WRITE], "\n", 1);
		line = my_readline("> ");
	}
	my_free(line);
	close(fd[F_WRITE]);
	fd[F_READ] = open(tmpname, O_RDONLY);
	unlink(tmpname);
	my_free(tmpname);
	if (dup2(fd[F_READ], STDIN_FILENO) == ERROR)
		return (print_error_str("here-doc", NULL, NULL, GENERAL_EXIT_CODE));
	close(fd[F_READ]);
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
			exit_code = redi_heredoc(token->next->token_str);
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
