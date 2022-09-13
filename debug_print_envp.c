
#include "minishell.h"

void print_dictionary_lst()
{
	int	i;
	t_dict	*cur;

	i = 0;
	while (i < DICT_MAX)
	{
		printf("category : %s\n", g_dict[i].value);
		cur = g_dict[i].next;
		while (cur)
		{
			printf("L %s=%s\n", cur->name, cur->value);
			cur = cur->next;
		}
		i++;
	}
}

void	print_envp(char *envp[])
{
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
}
