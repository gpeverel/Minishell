#include "../minishell.h"

char	*ft_path_command(char *path, char *command)
{
	char	*temp;
	char	*temp1;

	temp = ft_strjoin(path, "/");
	temp1 = ft_strjoin(temp, command);
	return (temp1);
}

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
	t_env	*temp;

	temp = ft_find_node(my_env, key);
	if (temp != NULL)
	{
		while (my_env != NULL)
		{
			len = ft_strlen(my_env->key);
			if (ft_strncmp(my_env->key, key, len) == 0)
			{
				return (&my_env->content);
			}
			my_env = my_env->next;
		}
	}
	return (NULL);
}

char	*ft_strcat(char *dst, char *src, char *three)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(dst) + ft_strlen(src) + ft_strlen(three);
	str = malloc(len + 1);
	while (dst[j] != '\0')
		str[i++] = dst[j++];
	j = 0;
	while (src[j] != '\0')
		str[i++] = src[j++];
	j = 0;
	while (three[j] != '\0')
		str[i++] = three[j++];
	str[i] = '\0';
	return (str);
}

void	ft_free_arr(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}
