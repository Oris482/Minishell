#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
 * < Dependency >
 * #include <unistd.h>
 *
 * < Prototype >
 * int ttyslot(void);
 *
 * < Description >
 * ttyslot을 호출한 프로그램이 참조하고 있는 터미널의 index를 반환한다.
 * 함수 수행에 문제가 생길 경우 이용하고 있는 시스템에 따라 0 혹은 -1이 반환된다.
 * 반환 받은 값은 터미널에 대한 DB의 엔트리 index로 이용되는데, ttyslot 함수의 경우 Legacy 함수라는 점을 참고하자.
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

	printf("TTYSLOT:\t%d\n", ttyslot());			// 문제 : 0 or -1 반환
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
