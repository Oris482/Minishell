#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	censor(int fd, const char *s)
{
	if (isatty(fd))
	{
		if (s)
			printf("%s에 referring하는 터미널입니다.\n", s);
		else
			printf("파일 디스크립트  %d 에 referring하는 터미널입니다.\n", fd);
	}
	else
	{
		if (s)
			printf("%s에 referring '안'하는 터미널입니다.\n", s);
		else
			printf("파일 디스크립트  %d 에 referring '안'하는 터미널입니다.\n", fd);
	}
}

int	main(void)
{
	int	fd;

	fd = open("test", O_RDONLY);
	if (fd < 0)
		return (1);
	censor(STDIN_FILENO, "STDIN");
	censor(STDOUT_FILENO, "STDOUT");
	censor(STDERR_FILENO, "STDERR");
	censor(fd, NULL);
	censor(42, NULL);
	close(fd);
	return (0);
}
