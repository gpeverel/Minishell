#include "../minishell.h"

t_env *ft_add_env(t_env *my_env, char *arg)
{
	char	*key;
	char	**content;
	char 	*arg_content;

	arg_content = ft_get_content(arg);
	key = ft_get_key(arg);
	content = ft_find_env(my_env, key);
	if (content != NULL)
	{
		free(*content);
		*content = arg_content;
	}
	else
	{
		ft_lstadd_back_env(&my_env, ft_lstnew_env(key, arg_content));
	}
	return (my_env);
}

int	ft_export(t_env *my_env, char **args)
{
	int i;

	i = 0;
	if (args[i] == NULL)
		ft_print_myenv(my_env, 1);
	else {
		//my_env = ft_create_my_env(args, my_env);
		while (args[i] != NULL)
		{
			my_env = ft_add_env(my_env, args[i]);
			i++;
		}
		//ft_print_myenv(my_env);
	}
	return (0);
}