#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "./lexer/lexer.h"

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	int				ret;
	char			*line;
	t_lx_token		*token_list;
	unsigned char	quote_flag;
	unsigned char	parentheses_flag;

	signal(SIGINT, handler);
	quote_flag = 0;
	parentheses_flag = 0;
	while (true)
	{
		if (!quote_flag && !parentheses_flag)
		{
			token_list = NULL;
			line = readline("$> ");
		}
		else
			line = readline("> ");
		if (line)
		{
			token_list = lexer(token_list, line, &quote_flag, &parentheses_flag);
			if ((strcmp(line, "")))
				add_history(line);
			free(line);
			line = NULL;
			if (!quote_flag && !parentheses_flag)
			{
				print_token_list(token_list);
				free(token_list);
			}
		}
		else
			return (1);
	}
	return (0);
}
