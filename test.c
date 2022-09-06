#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

void	classify(struct dirent *ent)
{
	printf("%s\t", ent->d_name);
	if (ent->d_type == DT_BLK)
		printf("Block Device\n");
	else if (ent->d_type == DT_CHR)
		printf("Character Device\n");
	else if (ent->d_type == DT_DIR)
		printf("Directory\n");
	else if (ent->d_type == DT_LNK)
		printf("Symbolic Link\n");
	else if (ent->d_type == DT_REG)
		printf("Regular File\n");
	else if (ent->d_type == DT_SOCK)
		printf("Unix Domain Socket\n");
	else
		printf("Unknown Type File\n");
}

int		main(void)
{
	int				temp;
	DIR				*dirp;
	struct dirent	*file;

	dirp = opendir(".");
	if (!dirp)
	{
		printf("error\n");
		return (1);
	}
	while (true)
	{
		temp = errno;
		file = readdir(dirp);
		if (!file && temp != errno)
		{
			printf("error\n");
			break ;
		}
		if (!file)
			break ;
		classify(file);
	}
	closedir(dirp);
	return (0);
}
