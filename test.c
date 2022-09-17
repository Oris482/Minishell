#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char *argv[], char *envp[])
{
	char	**input;

	input = (char **)malloc((ac + 1) * sizeof(char *));
	input[0] = strdup("ls");
	for (int i = 1; argv[i]; i++)
		input[i] = strdup(argv[i]);
	input[ac] = NULL;
	printf("\n\n@@@Main program started@@@\n\n");
	execve("/bin/ls", input, envp);
	perror("no");
	printf("\n@@@free program@@@\n\n");
	for (int i = 0; argv[i]; i++)
		free(input[i]);
	free(input);
	system("leaks -q a.out");
	return 1;
}

