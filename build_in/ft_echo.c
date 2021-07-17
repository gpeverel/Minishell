#include "../minishell.h"

void	ft_print_str(int fd, char **str, int i)
{
	int	error;

	error = all.error % 255;
	printf("error: %d\n", error);
	while (str[i] != NULL)
	{
		write(fd, &str[i][0], ft_strlen(&str[i][0]));
		write(fd, " ", 1);
		i++;
	}
}

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
		ft_print_str(fd, str, i);
	}
	if (flag == 0)
		write(fd, "\n", 1);
	all.error = 0;
	return (0);
}
