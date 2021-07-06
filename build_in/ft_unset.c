#include "../minishell.h"

t_env	*ft_find_node(t_env *my_env, char *key)
{
	size_t	len;

	while (my_env != NULL)
	{
		len = ft_strlen(my_env->key);
		if (ft_strncmp(my_env->key, key, len) == 0)
		{
			//printf("my_env->key=%s\n\n", my_env->key);
			//printf("my_env=%p\n\n", my_env);
			return (my_env);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

t_env	*ft_unset(t_env *my_env, char **args)
{
	int 	i;
	t_env	*temp;
	t_env	*prev;
	t_env	*next;

	i = 0;
	while (args[i] != NULL)
	{
		//printf("%s\n\n", args[i]);
		temp = ft_find_node(my_env, args[i]);
		//printf("temp=%p\n\n", temp);
		if(temp != NULL)
		{
			prev = (temp)->prev;
			next = (temp)->next;
			if (prev != NULL)
				prev->next = next;
			else
				my_env = my_env->next;
			if (next != NULL)
				next->prev = prev;
			free((temp)->content);
			free(temp);
			(temp) = NULL;
		}
		i++;
	}
	return (my_env);
}

