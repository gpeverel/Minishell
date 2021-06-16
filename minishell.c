#include "minishell.h"
//char *str; // глобальная переменная для главной команды

char *ft_error(char *err)
{
	printf("%s\n", err);
	return (NULL);
}

char	*pars_bucket(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	//printf("%s\n", tmp);
	//free(str);
	return tmp;
}

char	*pars_double_bucket(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
		 || str[*i + 1] == '$' || str[*i + 1] == '\\'))

		if (str[*i] == '\"')
			break;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	//printf("%s\n", tmp);
	free(str);
	return tmp;

}

char	*pars_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	//(*i)++;
	//if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '\\' ||
	// str[*i] == '\t'/* || str[*i] == '\'*/ || str[*i] == '\n')
	//	tmp2 = ft_strdup(str + *i);
	//else
		tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(str);
	(*i)++;
	printf("%s\n", tmp);
	return(tmp);
}

char	*command_parser(char *str, char **env)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = pars_bucket(str, &i);
		if (str[i] == '\"')
			str = pars_double_bucket(str, &i);
		if (str[i] == '\\')
			str = pars_slesh(str, &i);
		if (str[i] == '$')
			str = pars_dollar(str, &i, env);
		//if (str[i] == '')
		//	str = pars_bucket(str, &i);
	}
	return str;
}

int		main(int argc, char** argv, char **env)
{
	char *str = "awsd' $sd '_$USER #ggh asdf";

		//while (*argv)
		//{
			//command_pre_parser(str);
			str = command_parser(str, env);
			//printf("%s", str);
		//}





}
