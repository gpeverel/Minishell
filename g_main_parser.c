#include "minishell.h"

char	*delete_space(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = *i;
	if (*i == 0)
	{
		while (str[j] == ' ')
			j++;
		return(tmp = ft_strdup(str + j));
	}
	while (str[j] == ' ')
		j++;
	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + j - 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	return (tmp);
}

char	*init_arg(char *str, int start, int end)
{
	char	*arg;
	int		i;

	i = 0;
	arg = malloc((end - start) + 1);
	while (start < end)
	{
		arg[i] = str[start];
		start++;
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char	*check_main_symbols_str(char *str, int *i, char **env)
{
	if (str[*i] == '\'')
		str = pars_bucket(str, i);
	if (str[*i] == '\"')
		str = pars_double_bucket(str, i, env);
	if (str[*i] == '\\')
		str = pars_slesh(str, i);
	if (str[*i] == '$')
		str = pars_dollar(str, i, env);
	return (str);
}