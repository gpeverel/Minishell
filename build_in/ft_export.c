#include "../minishell.h"

/*char	*ft_print_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (NULL);
}*/

/*char **ft_paste_env(char **env, char *arg)
{
	int size;
	int	i;
	char	**new_env;

	i = 0;
	size = 0;
	while (env[size] != NULL)
		size++;
	if ((new_env = malloc((size + 2) * sizeof(char *))) == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	new_env[i] = ft_strdup(arg);
	new_env[++i] = NULL;
	return (new_env);
}*/

int	ft_export(t_env *my_env, char **args)
{
	int i;

	i = 0;
	if (args[i] == NULL)
		ft_print_myenv(my_env);
	else {
		my_env = ft_create_my_env(args, my_env);
		//ft_print_myenv(my_env);
	}
	return (0);
}