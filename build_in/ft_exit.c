#include "../minishell.h"

void	ft_exit(char **args)
{
	int i;
	int	code;

	i = 0;
	code = ft_atoi(args[0]) % 256;
	printf("code= %d\n", code);
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		printf("exit: too many arguments\n");
	}
	else
		exit(code);
}
