#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(GENERAL_EXIT_CODE);
	rl_replace_line("", 1);
	rl_redisplay();
}

int		main(void)
{
	int				ret;
	char			*line;

	signal(SIGINT, handler);
	while (true)
	{
		line = readline("input> ");		// '\n' 빈문자로 인식
		if (line)
		{
			ret = strcmp(line, "bye");
			if (ret)
				printf("output> %s\n", line);
			if ((strcmp(line, "")))
				add_history(line);
			free(line);
			line = NULL;
			if (!ret)
				break ;
		}
		else
			return (1);
	}
	return (0);
}
