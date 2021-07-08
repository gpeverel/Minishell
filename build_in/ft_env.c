#include "../minishell.h"

char	*ft_get_content(char *source)
{
	int		i;
	char	*str;

	i = 0;
	while (source[i] != '=' && source[i] != '\0')
		i++;
	if(i == ft_strlen(source))
		str = NULL;
	else
	{
		i++;
		str = ft_strdup(&source[i]);
	}
	return (str);
}

char	*ft_get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	str[i] = '\0';
	return (str);
}

t_env	*ft_create_my_env(char **env, t_env *my_env)
{
	int		i;
	char	*key;
	char	*content;

	i = 0;
	if (my_env == NULL)
	{
		my_env = ft_lstnew_env("_", getcwd(NULL, 0));
	}
	while (env[i] != NULL)
	{
		content = ft_get_content(env[i]);
		key = ft_get_key(env[i]);
		ft_lstadd_back_env(&my_env, ft_lstnew_env(key, content));
		i++;
	}
	return (my_env);
}
