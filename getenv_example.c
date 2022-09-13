
#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*cur;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		cur = envp[i];
		while (*cur)
		{
			ft_putchar_fd(*cur, STDOUT_FILENO);
			cur++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (0);
}
