#include "minishell.h"

char *ft_error(char *err)
{
	printf("%s\n", err);
	return (NULL);
}

char	*pars_bucket(char *str, int *i)// без ликов
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
	free(str);
	free(tmp2);
	free(tmp3);
	(*i)-= 1;
	return tmp;
}

char	*pars_double_bucket(char *str, int *i, char **env)// без ликов
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	++(*i);
	while (str[(*i)])
	{
		if (str[*i] == '$')
		{
			str = pars_dollar(str, i, env);// добавил str =
			continue;
		}
		if (str[*i] == '\"')
			break;
		++(*i);
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + (*i)-- + 1);// уменьшаю I на 1 чтобы не переходить
	tmp = ft_strjoin(tmp, tmp2);//			к следующему символу
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	free(str);
	return tmp;
}

char	*command_parser(char *str, char **env)
{
	int		i;
	int		check_start_arg;
	char	*arg;

	i = 0;
	check_start_arg = -1;
	if (str[i] == ' ' && i == 0)
		str = delete_space(str, &i);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break;// защита от пробелов в конце
		all.check_dol = 0;
		check_start_arg = i;
		str = check_main_symbols_str(str, &i, env);
		if (all.check_dol != 1)
		{
			arg = init_arg(str, check_start_arg, i);
			push_elem(arg);
			printf("|%s|\n", arg);
			//continue;// вроде не нужен
		}
	}
	show_list();
	return (str);

}

// сделать так чтобы редирект брал все от начала стрелки до конца названия файла
// и потом проверять что за стрелка, когда уже определяю тип в списке,
// затем уже отделить стрелку от названия файла и запихнуть куда надо

int		main(int argc, char** argv, char **env)
{
	int	i = 0;
	int	len;

	//char	*str1 = "   echo >>  $USER  \"NAME\"USER\"\'_file\'\"  <\'2file\'\"_best^\"";
	//char	*str1 = "   echo  >> \"$MYY?$USER$MY very\">ASD\"asd\"";
	char	*str1 = "   echo  >>\"first\"     >>  \"get\"$USER\"  !!!\"   Second\"asd\"";
	//char	*str1 = "   echo   Second\"asd\"   ";
	len = ft_strlen(str1);
	char *str = ft_calloc(len + 1, 1);
	while (i < len)
	{
		str[i] = str1[i];
		i++;
	}

	push_command_in_history(str);

	initstruct();// инициализируем все поля в структуре
	printf("mainStr = %s|\n", str);
	//while (*argv)
	//{
		i = command_pre_parser(str);
		if (i != -1)
			str = command_parser(str, env);
		free(str);
		//printf("%s", str);
		// while (1)
		// {}





}
