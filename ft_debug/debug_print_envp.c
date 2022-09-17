
#include "minishell_info.h"

int print_dictionary_lst()
{
	int	i;
	int	total = 0;
	t_dict	*cur;

	i = 0;
	while (i < DICT_MAX)
	{
		printf("category : %s\n", g_dict[i].value);
		cur = g_dict[i].next;
		while (cur)
		{
			printf("L %s=%s\n", cur->name, cur->value);
			total++;
			cur = cur->next;
		}
		i++;
	}
	return (total);
}

int	print_strs(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i])
		printf("%s\n", strs[i++]);
	return (i);
}
