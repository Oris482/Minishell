#include <stdio.h>

void ft_strjoin_myself(char **str, char *add)
{
	char *new;

	if (!str)
		return ;
	new = (char *)malloc(sizeof(char) * ())
	if (!new)
		return ;
	if (str)
	str
	ft_strcpy();
	if (*str)
		free(*str);

}

int main(int ac, char *argv[])
{
	int		i;
	char	*str;

	str = NULL;
	printf("before : %s\n", str);
	if (ac < 1)
		return (1);
	i = 1;
	while (argv[i])
	{
		ft_strjoin_myself(&str, argv[i]);
		i++;
	}
	printf("after : %s\n", str);
	return (0);
}
