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

int	main(int argc, char *argv[], char *envp[])
{
	// int				ret;
	char			*full_line;
	t_lx_token		*token_list;

	signal(SIGINT, handler);
	while (true)
	{
		token_list = NULL;
		full_line = line_handler();
		if (!full_line)					// ERROR malloc 실패와 같은 정말 특수 상황?
			return (1);
		if (strcmp(full_line, "") != 0)
			add_history(full_line);
		token_list = lexer(token_list, full_line, envp);
		free(full_line);
	    full_line = NULL;
		print_token_list(token_list);
		free(token_list);
	}
	return (0);
}

