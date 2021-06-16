#include "minishell.h"

char	*pars_redir_one(char *str, int *i, char **env)
{
	int j;
	int	z;
	char	*tmp;

	j = *i + 1;
	while (str[j] == ' ' || str[j] == '\t')
	{
		j++;
	}
		printf("%d\n", j);
	z = --j;
	while (str[++j])
	{
		if (str[j] == '\'')
			str = pars_bucket(str, &j);
		if (str[j] == '\"')
			str = pars_double_bucket(str, &j, env);
		if (str[j] == '\\')
			str = pars_slesh(str, &j);
		if (str[j] == '$')
			str = pars_dollar(str, &j, env);
		if (str[j] == '>' || str[j] == '<')
		{
			printf("%d\n", j);
			ft_error("Redirect error\n");
		}
		if (str[j] == ' ' || str[j] == '\t')
			break;
	}
	//*i = j;
	tmp = ft_substr(str, 0, *i - 1);
	tmp = ft_strjoin(tmp, str + j);
	free(str);
	return (tmp);

}