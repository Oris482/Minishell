/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:50:16 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/21 22:24:57 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "ft_print.h"
#include "ft_token.h"

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

int	redi_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return (handle_redirections_error("Redi-in", filename));
	my_dup2(fd, STDIN_FILENO);
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
	my_dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS_EXIT_CODE);
}

int	redi_middleware(t_lx_token *token)
{
	int		exit_code;
	char	*err_arg;

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
		err_arg = token->next->token_str;
		token = token->next->next;
	}
	if (exit_code == SUCCESS_EXIT_CODE && token != NULL)
		return (print_error_str("Redirect", err_arg, \
								"ambigous redirect", GENERAL_EXIT_CODE));
	return (exit_code);
}
