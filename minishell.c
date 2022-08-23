#include "minishell.h"
// #include "lexer.h"
// #include "liner.h"
#include "lexer/lexer.h"
#include "liner/liner.h"

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
	// int				ret;
	char			*line;
	// t_lx_token		*token_list;

	signal(SIGINT, handler);
	while (true)
	{
		// token_list = NULL;
		line = line_handler();
		if (!line)					// ERROR malloc 실패와 같은 정말 특수 상황?
			return (1);
		if (strcmp(line, "") != 0)
			add_history(line);
		// if (!quote_flag && !parentheses_flag)
		// {
		//     token_list = NULL;
		//     line = readline("$> ");
		// }
		// else
		//     line = readline("> ");

		// if (line)
		// {
		//     free(line);
		//     line = NULL;
		//     if (!quote_flag && !parentheses_flag)
		//     {
		//         print_token_list(token_list);
		//         free(token_list);
		//     }
		// }
		// else
		//     return (1);
	}
	return (0);
}

