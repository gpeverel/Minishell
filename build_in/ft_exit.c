#include "../minishell.h"

void ft_check_letter(char *args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
		{
			printf("exit: fd: numeric argument required\n");
			exit(255);
		}
		i++;
	}
}

void	ft_exit(char **args)
{
	int i;
	int	code;

	i = 0;
	ft_check_letter(args[0]);
	code = ft_atoi(args[0]) % 256;
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		errno = 1;
		printf("exit: too many arguments\n");
	}
	else
		exit(code);
}
