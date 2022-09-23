/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:22:59 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/22 23:12:26 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "ft_command.h"
#include "minishell.h"
#include "ft_print.h"
#include "ft_string.h"
#include "ft_check.h"
#include "ft_alloc.h"
#include "ft_token.h"

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

int	make_tmp_heredoc(t_dict dict[], t_lx_token *token, char *pure_limiter)
{
	int				write_fd;
	pid_t			pid;
	int				status;
	char			*tmpname;
	t_heredoc_info	heredoc_info;

	_set_heredoc_info(&heredoc_info, pure_limiter);
	if (make_tmpfile(dict, &tmpname, &write_fd) == FALSE)
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

static void	_translate_heredoc_line(t_dict dict[], char *line, int write_fd, \
														int translate_option)
{
	t_lx_token	*token_tmp;
	char		*chunk;
	char		*pos;

	if (translate_option)
	{
		token_tmp = make_token_node(ft_strdup(line), WORD);
		token_tmp->token_str[ft_strlen(token_tmp->token_str) - 1] = '\0';
		chunk = token_tmp->token_str;
		while (*chunk)
		{
			pos = ft_strchr_null(chunk, '$');
			ft_strjoin_self_add_free(&token_tmp->interpreted_str, \
														ft_strcpy(chunk, pos));
			chunk = pos;
			if (*chunk != '\0')
				dollar_translator(dict, token_tmp, &chunk, DOLLAR | DQUOTE);
		}
		ft_putendl_fd(token_tmp->interpreted_str, write_fd);
		my_multi_free(token_tmp->token_str, token_tmp->interpreted_str, \
															token_tmp, NULL);
	}
	else
		ft_putstr_fd(line, write_fd);
	my_free(line);
}

static void	_translate_heredoc_file(t_dict dict[], t_lx_token *token)
{
	const char	*old_filename = token->interpreted_str;
	char		*new_filename;
	char		*line;
	int			translate_option;
	int			fd[2];

	fd[F_READ] = open(old_filename, O_RDONLY);
	if (make_tmpfile(dict, &new_filename, &fd[F_WRITE]) == FALSE)
		exit(print_error_str("heredoc", NULL, NULL, GENERAL_EXIT_CODE));
	line = get_next_line(fd[F_READ]);
	translate_option = FALSE;
	if (line && *line == 't')
		translate_option = TRUE;
	my_free(line);
	line = get_next_line(fd[F_READ]);
	while (line)
	{
		_translate_heredoc_line(dict, line, fd[F_WRITE], translate_option);
		line = get_next_line(fd[F_READ]);
	}
	close(fd[F_READ]);
	close(fd[F_WRITE]);
	unlink(old_filename);
	token->interpreted_str = new_filename;
	my_multi_free(line, (char *)old_filename, NULL, NULL);
}

int	redi_heredoc(t_dict dict[], t_lx_token *token)
{
	int		read_fd;
	char	*filename;

	_translate_heredoc_file(dict, token);
	filename = token->interpreted_str;
	read_fd = open(filename, O_RDONLY);
	if (read_fd == ERROR)
		return (print_error_str("here-doc", NULL, \
					"can't open tmp file", GENERAL_EXIT_CODE));
	my_dup2(read_fd, STDIN_FILENO);
	close(read_fd);
	return (SUCCESS_EXIT_CODE);
}
