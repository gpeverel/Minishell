#include "../minishell.h"

int ft_echo(char **str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (ft_strcmp(str[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (str[i] != NULL)
	{
		printf("%s ", str[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
