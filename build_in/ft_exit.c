#include "../minishell.h"

void	ft_exit(char **args)
{
	int i;
	int	code;

	i = 0;
	code = 0;
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		errno = 1;
		printf("error cd: %s\n", strerror(errno));
	}
	else
		exit(code);
}
