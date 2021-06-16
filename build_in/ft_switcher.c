#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (src1[i] != '\0' || src2[i] != '\0')
	{
		if (src1[i] == '\0' && src2[i] == '\0')
			return (0);
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}

int	ft_switcher(char **args, char **env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args[1]); //todo: может быть несколько аргументов
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(&args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else
		printf("no");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	ft_switcher(&argv[1], env);
	return (0);
}
