
#include "minishell.h"

void print_dicttionary_lst()
{
	int	i;
	t_dict	*cur;

	i = 0;
	while (i < DICT_MAX)
	{
		printf("category : %s\n", g_dic[i].value);
		cur = g_dic[i].next;
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
