#include "minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*get_key_in_env(t_env *my_env, char *key)
{
	t_env	*env;

	env = my_env;
	if (key[0] == '?')
	{
		return (ft_itoa(all.error));
	}
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strnewcpy(env->content, ft_strlen(env->content)));
		env = env->next;
	}
	return (NULL);
}

int	go_to_end_key(char *tmp2, int z)
{
	int	i;

	i = 0;
	while (tmp2[i])
		i++;
	i += z;
	all.check_dol = 2;
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
	while_key_end(i, str);
	if (*i == j + 1 && str[*i] != '?')
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = get_key_in_env(my_env, key);
	free(key);
	key = ft_substr(str, 0, j);
	if (tmp2 == NULL)
		if_str_null(&tmp2, str, i);
	else
	{
		z = go_to_end_key(tmp2, z);
		key = ft_strjoin(key, tmp2);
		free(tmp2);
		tmp2 = ft_substr(str, *i, ft_strlen(str) - *i);
	}
	*i = z;
	return (join_all_part(&key, tmp2, str));
}
