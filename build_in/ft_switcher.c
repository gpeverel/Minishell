#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	if (src1 == NULL || src2 == NULL)
		return (-1);
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

char	**ft_find_env(t_env *my_env, char *key)
{
	size_t	len;

	while (my_env != NULL)
	{
		len = ft_strlen(my_env->key);
		if (ft_strncmp(my_env->key, key, len) == 0)
		{
			return (&my_env->content);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

int	ft_switcher(char **args, char **env)
{
	int		fd;
	t_env	*my_env;

	fd = 1;
	my_env = ft_create_my_env(env, NULL);
//ft_print_myenv(my_env, 0);
//printf("\n\n");
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(my_env, args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd, &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(my_env, &args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_print_myenv(my_env, 0);
	else if (ft_strcmp(args[0], "unset") == 0)
		my_env = ft_unset(my_env, &args[1]);
/*	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(&args[1]);*/
	else
		printf("no\n");
//ft_print_myenv(my_env, 0);
	ft_lstclear_env(&my_env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 1)
		ft_switcher(&argv[1], env);
	while (1);
	return (0);
}
