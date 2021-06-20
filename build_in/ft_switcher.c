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

char	*ft_find_env(char **env, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	while (env[i] != NULL)
	{
		len = ft_strlen(key);
		if (ft_strncmp(&env[i][0], key, len) == 0)
			return (&env[i][len]);
		i++;
	}
	return (NULL);
}

char **ft_create_my_env(char **env)
{
	int size;
	int	i;
	char	**my_env;

	i = 0;
	size = 0;
	while (env[size] != NULL)
		size++;
	if ((my_env = (char **)malloc((size + 2) * sizeof(char *))) == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		//todo: добавить кавычки у аргументов
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = ft_strjoin("_=", getcwd(NULL, 0));
	i++;
	my_env[i] = NULL;
	return (my_env);
}

int	ft_switcher(char **args, char **env)
{
	int fd;
	char **my_env;

	fd = 1;
	my_env = ft_create_my_env(env);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args[1], ft_find_env(env, "HOME="));
	//todo: может быть несколько аргументов
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd, &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(&args[1], my_env);
	else
		printf("no");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	ft_switcher(&argv[1], env);
	while (1);
	return (0);
}
