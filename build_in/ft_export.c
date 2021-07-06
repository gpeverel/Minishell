#include "../minishell.h"

t_env *ft_add_env(t_env *my_env, char *arg)
{
	char	*key;
	char	**content;

	key = ft_get_key(arg);
	content = ft_find_env(my_env, key);
	if (content != NULL)
	{
		//*content = ft_get_content(arg);
	}
	else
	{
		ft_lstadd_back_env(&my_env, ft_lstnew_env(key, ft_get_content(arg)));
	}
	return my_env;
}

int	ft_export(t_env *my_env, char **args)
{
	int i;

	i = 0;
	if (args[i] == NULL)
		ft_print_myenv(my_env);
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