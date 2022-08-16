#include <unistd.h>			// for getcwd()
#include <stdio.h>			// for printf()
#include <stdlib.h>			// for free()

int	main(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	path = NULL;
	return (0);
}
