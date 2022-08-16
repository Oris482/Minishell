#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
 * < Dependency >
 * #include <unistd.h>
 *
 * < Prototype >
 * char *ttyname(int fd);
 *
 * < Description >
 * 인자로 받은 fd라는 파일 디스크립터가 터미널을 참조하고 있다면, 해당 터미널의 경로를 '\0'라는 널 문자로 종료되는 문자열로 반환한다.
 * 만일 함수 수행에 문제가 있거나 fd가 터미널을 참조하고 있지 않다면, NULL을 반환한다.
 * 반환 받은 문자열은 내부적으로 static 형태로 할당되어 있기 때문에 ttyname의 연이은 호출에 의해 그 값이 덮어쓰일 수 있다.
 * 또한 static 형태로 할당되었으므로 별도의 free 호출은 하지 않아도 된다.
 */

void	censor(int fd, const char *s)
{
	if (isatty(fd))
	{
		if (s)
			printf("%s is referring to a terminal\n", s);
		else
			printf("File Descriptor %d is referring to a terminal\n", fd);
	}
	else
	{
		if (s)
			printf("%s is not referring to a terminal\n", s);
		else
			printf("File Descriptor %d is not referring to a terminal\n", fd);
	}
	printf("TTYNAME:\t%s\n", ttyname(fd));
}

int	main(void)
{
	int	fd;

	fd = open("./test", O_RDONLY);
	printf("fd : %d\n", fd);
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
