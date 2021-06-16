#include "minishell.h"

int		ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*find_key_env(char **env, char *key, int *k, int *z)
{
	char	*tmp2;

	if (ft_strnstr(env[*k], key, ft_strlen(env[*k])))
		{
			*z = 0;
			while (env[*k][*z] != '=' && env[*k][*z])
				(*z)++;
			tmp2 = ft_substr(env[*k], 0, *z);// собираю все до =
			if (ft_strncmp(key, tmp2, ft_strlen(env[*k])) == 0)
			{// нахожу в команде ключ
				free(tmp2);
				return (NULL);
			}
			free(tmp2);
		}
	tmp2 = "0";// чтобы потом проверить на NULL
	return (tmp2);
}

char	*get_key_in_env(char **env, char *key)
{
	char	*tmp2;
	int		k;
	int		z;

	z = 0;
	k = -1;
	while (env[++k])
	{
		// if (ft_strnstr(env[k], key, ft_strlen(env[k])))
		// {
		// 	z = 0;
		// 	while (env[k][z] != '=' && env[k][z])
		// 		z++;
		// 	//tmp2 = ft_strnstr(env[k], )
		// 	tmp2 = ft_substr(env[k], 0, z);// собираю все до =
		// 	if (ft_strncmp(key, tmp2, ft_strlen(env[k])) == 0)
		// 	{// нахожу в команде ключ
		// 		free(tmp2);
		// 		tmp2 = NULL;
		// 		break ;
		// 	}
		// 	free(tmp2);
		// }
		tmp2 = find_key_env(env, key, &k, &z);
		if (tmp2 == NULL)// значит нашел
			break ;
		//tmp2 = "0";// чтобы потом проверить на NULL
	}
	if (tmp2 != NULL)
		return (NULL);
	tmp2 = ft_substr(env[k], z + 1, ft_strlen(env[k]) - z);
	return (tmp2);
}

char	*pars_dollar(char *str, int *i, char **env)
{
	char	*key;
	char	*tmp2;
	int		j;

	j = *i;
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);// взяли ключ
	tmp2 = get_key_in_env(env, key);// получили наше значение
	free(key);
	key = ft_substr(str, 0, j);// взяли все до $
	if (tmp2 == NULL)
		tmp2 = ft_strdup(str + *i);// пропустили весь ключ
	else
	{// если ключ нашли то берем его и все что после него
		key = ft_strjoin(key, tmp2);
		free(tmp2);
		tmp2 = ft_substr(str, *i, ft_strlen(str) - *i);
	}
	key = ft_strjoin(key, tmp2);
	free(tmp2);
	printf("%s\n", key);
	free(str);
	return key;
}