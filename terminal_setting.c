#include "./minishell.h"

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

void	signal_handler()
{
	signal(SIGINT, _sigint_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
}

int	terminal_off_control_chars()
{
	struct termios termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (SUCCESS);
}