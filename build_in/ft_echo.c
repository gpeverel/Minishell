#include "../minishell.h"

int	ft_echo(int fd, char **str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] != NULL)
	{
		while (ft_strcmp(str[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		while (str[i] != NULL)
		{
			write(fd, str[i], ft_strlen(str[i]));
			write(fd, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(fd, "\n", 1);
	return (0);
}
