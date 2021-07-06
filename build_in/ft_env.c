#include "../minishell.h"

char *ft_get_content(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return &str[i];
}

char *ft_get_key(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=')
		i++;
	str[i] = '\0';
	return str;
}

t_env *ft_create_my_env(char **env)
{
	/*int size;
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
	return (my_env);*/

	int		i;
	t_env	*my_env;
	char 	*key;
	char 	*content;

	i = 0;
	my_env = ft_lstnew_env("_", "test");
	while (env[i] != NULL)
	{
		content = ft_get_content(env[i]);
		key = ft_get_key(env[i]);;
		ft_lstadd_back_env(&my_env, ft_lstnew_env(key, content));
		i++;
	}
	return (my_env);
}

