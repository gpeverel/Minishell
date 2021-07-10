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

char	*pars_double_bucket(char *str, int *i, t_env *my_env)// без ликов
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
			str = pars_dollar(str, i, my_env);// добавил str =
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

char	*command_parser(char *str, t_env *my_env)
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
		str = check_main_symbols_str(str, &i, my_env);
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
	int		i = 0;
	//int	len;
	int		fd;
	t_env	*my_env;
	char	*str;

	//char	*str1 = "   echo >>  $USER  \"NAME\"USER\"\'_file\'\"  <\'2file\'\"_best^\"";
	//char	*str1 = "   echo  >> \"$MYY?$USER$MY very\">ASD\"asd\"";
	//char	*str1 = "   echo  >>\"first\"     >>  \"get\"$USER\"  !!!\"  $USER Second\"asd\"";
	//char	*str1 = "   echo   Second\"asd\"   ";
	//char	*str1 = "   echo $USERR  Second\"asd\"   ";
	// char *str1 = " $MYY|$MY |\"bucket\"|\'awdASD\'  |"; // проверка пайпов
	// len = ft_strlen(str1);
	// char *str = ft_calloc(len + 1, 1);
	// while (i < len)
	// {
	// 	str[i] = str1[i];
	// 	i++;
	// }
	//printf("mainStr = %s|\n", str);

	my_env = ft_create_my_env(env, NULL);
	get_history_from_file();

	fd = open("fhistory", O_WRONLY | O_APPEND, 0644);
	int z = 0;
	while (1)
	{
		initstruct();// инициализируем все поля в структуре
		str = readline ("syka_write: ");
		//if (ft_strncmp("stop", str, 4) == 0)
		//	break;
		if (str && *str)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			add_history(str);
			i = command_pre_parser(str);
			if (i != -1)
				str = command_parser(str, my_env);

			ft_adapter(my_env);
			free(str);
			del_all_pars_list();
			//printf("str = %s\n", str);
			//z++;
		}
	}
	close(fd);
	//printf("%s", str);
	ft_lstclear_env(&my_env);
		//while (1)
		//{}
	return (0);


}
