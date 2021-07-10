#include "minishell.h"

int		ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

// char	*find_key_env(t_env *my_env, char *key, int *k, int *z)
// {
// 	char	*tmp2;
// 	if (ft_strnstr(my_env[*k], key, ft_strlen(my_env[*k])))
// 		{
// 			*z = 0;
// 			while (my_env[*k][*z] != '=' && my_env[*k][*z])
// 				(*z)++;
// 			tmp2 = ft_substr(my_env[*k], 0, *z);// собираю все до =
// 			if (ft_strncmp(key, tmp2, ft_strlen(my_env[*k])) == 0)
// 			{// нахожу в команде ключ
// 				free(tmp2);
// 				return (NULL);
// 			}
// 			free(tmp2);
// 		}
// 	tmp2 = "0";// чтобы потом проверить на NULL
// 	return (tmp2);
// }
//
// char	*get_key_in_env(t_env *my_env, char *key)
// {
// 	char	*tmp2;
// 	int		k;
// 	int		z;
// 	t_env	*env_tmp;
// 	env_tmp = my_env;
// 	z = 0;
// 	k = -1;
// 	while (env_tmp)
// 	{
// 		tmp2 = find_key_env(env_tmp, key, &k, &z);
// 		//printf("%s\n", tmp2);
// 		if (tmp2 == NULL)// значит нашел
// 			break ;
// 		//tmp2 = "0";// чтобы потом проверить на NULL
// 		env_tmp = env_tmp->next;
// 	}
// 	if (tmp2 != NULL)
// 		return (NULL);
// 	tmp2 = ft_substr(my_env[k], z + 1, ft_strlen(env[k]) - z);
// 	//printf("\n%s\n", tmp2);
// 	return (tmp2);
// }

char	*get_key_in_env(t_env *my_env, char *key)
{
	t_env	*env;
	char	*item;

	env = my_env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return(ft_strnewcpy(env->content, ft_strlen(env->content)));
		env = env->next;
	}
	return (NULL);
}

int		go_to_end_key(char *tmp2, int z)
{
	int	i;

	i = 0;
	while (tmp2[i])
		i++;
	i += z;
	return (i);
}

char	*pars_dollar(char *str, int *i, t_env *my_env)
{
	char	*key;
	char	*tmp2;
	int		j;
	int		z;

	z = *i;
	j = *i;
	// while (str[++(*i)])
	// 	if (!ifkey(str[*i]))
	// 		break ;
	while_key_end(i, str);
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);// взяли ключ
	tmp2 = get_key_in_env(my_env, key);// получили наше значение
	free(key);
	key = ft_substr(str, 0, j);// взяли все до $
	if (tmp2 == NULL)
		if_str_null(&tmp2, str, i);
	//{
		// tmp2 = ft_strdup(str + *i);// пропустили весь ключ
		// if (all.check_dol != 2)// если перед $ были другие символы
		// 	all.check_dol = 1;// чтобы нормально работать с пробелами при парсере
	//}
	else
	{// если ключ нашли то берем его и все что после него
		z = go_to_end_key(tmp2, z);
		key = ft_strjoin(key, tmp2);
		free(tmp2);
		all.check_dol = 2;// опасно, добавил для пайпов
		tmp2 = ft_substr(str, *i, ft_strlen(str) - *i);
	}
	*i = z;
	return (join_all_part(&key, tmp2, str));
	// key = ft_strjoin(key, tmp2);
	// free(tmp2);//printf("%s\n", key);
	// free(str);
	// return key;
}