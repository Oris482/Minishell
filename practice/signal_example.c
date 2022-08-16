#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

void	handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "write From Signal\n", 18);
}

int	main(void)
{
	signal(SIGINT, handler);
	while(true)
		;
	return (0);
}
