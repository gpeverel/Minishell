#include "../minishell.h"

t_env	*ft_find_node(t_env *my_env, char *key)
{
	size_t	len;

	while (my_env != NULL)
	{
		len = ft_strlen(my_env->key);
		if (ft_strncmp(my_env->key, key, len) == 0)
		{
			return (my_env);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

t_env	*ft_unset(t_env *my_env, char **args)
{
	int		i;
	t_env	*temp;
	t_env	*next;

	i = 0;
	while (args[i] != NULL)
	{
		temp = ft_find_node(my_env, args[i]);
		if (temp != NULL)
		{
			next = (temp)->next;
			if ((temp)->prev != NULL)
				(temp)->prev->next = next;
			else
				my_env = my_env->next;
			if (next != NULL)
				next->prev = (temp)->prev;
			free((temp)->content);
			free(temp);
			(temp) = NULL;
		}
		i++;
	}
	return (my_env);
}
