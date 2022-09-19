#include <unistd.h>
#include <stdlib.h>
#include "../minishell_info.h"

int	my_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (ret);
}

int	my_pipe(int files[2])
{
	int	ret;

	ret = pipe(files);
	if (ret == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (ret);
}

pid_t	my_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (pid);
}

int	my_close(int fildes)
{
	int	ret;

	ret = close(fildes);
	if (ret == ERROR)
		exit(GENERAL_EXIT_CODE);
	return (ret);
}
