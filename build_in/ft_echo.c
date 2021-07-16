#include "../minishell.h"

void	ft_print_str(int fd, char **str, int i)
{
	int	j;
	int	error;

	j = 0;
	error = all.error % 255;
	printf("error: %d\n", error);
	while (str[i] != NULL)
	{
		while (str[i][j] == '$' && str[i][j + 1] == '?')
		{
			printf("error: %d\n", error);
			ft_putnbr_fd(error, fd);
			printf("error: %d\n", error);
			j = j + 2;
		}
		write(fd, &str[i][j], ft_strlen(&str[i][j]));
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
