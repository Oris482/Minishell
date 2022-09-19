/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:07:18 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/09/18 20:15:24 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_info.h"
#include "minishell.h"

static void	_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			exit(GENERAL_EXIT_CODE);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	set_init_signal(void)
{
	signal(SIGINT, _sigint_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void	set_int_quit_signal(void *sigint_action, void *sigquit_action)
{
	signal(SIGINT, sigint_action);
	signal(SIGQUIT, sigquit_action);
}

int	terminal_off_control_chars(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (SUCCESS);
}

int	terminal_on_control_chars(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	termios_p.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (SUCCESS);
}
