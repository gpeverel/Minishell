#include "minishell.h"

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
	free(str);
	(*i) -= 2;
	return tmp;
}

char	*pars_double_bucket(char *str, int *i, char **env)
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
			str = pars_slesh(str, i);
		if (str[*i] == '$')
			pars_dollar(str, i, env);
		if (str[*i] == '\"')
			break;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + (*i)-- + 1);// уменьшаю I на 1 чтобы не переходить
	tmp = ft_strjoin(tmp, tmp2);//			к следующему символу
	tmp = ft_strjoin(tmp, tmp3);
	//printf("%s\n", tmp);
	free(tmp2);
	free(tmp3);
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
	//printf("%s\n", tmp);
	return(tmp);
}

// char	*command_parser(char *str, char **env) // старый вариант без разделения на аргументы
// {
// 	int i;
// 	int	check_start_arg;
// 	check_start_arg = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
		// if (str[i] == ' ' && i == 0)// для того чтобы убрать пробелы перед командой
		// 	str = pars_dollar(str, &i, env);
		// if (str[i] == '\'')
		// 	str = pars_bucket(str, &i);
		// if (str[i] == '\"')
		// 	str = pars_double_bucket(str, &i, env);
		// if (str[i] == '\\')
		// 	str = pars_slesh(str, &i);
		// if (str[i] == '$')
		// 	str = pars_dollar(str, &i, env);
		// if (str[i] == ' ')
		// {
		// 	str = delete_space(str, &i);
		// }
// 		if (str[i] == '>' || str[i] == '<')// dup2 написать функцию которая перенаправляет ввод на редиректы
// 			str = pars_redir_one(str, &i, env);
// 	}
// 	return str;
// }

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
		check_start_arg = i;
		str = check_main_symbols_str(str, &i, env);
		while (str[i])
		{
			if (str[i] == ' ' || str[i + 1] == '\0')
			{
				arg = init_arg(str, check_start_arg, i);
				str = delete_space(str, &i);
				i++;
				printf("\n%s|\n", arg);

				break;
			}
			i++;
		}
	}
	return (str);

}

// начать разделять всю команду по частям и флаги тоже

int		main(int argc, char** argv, char **env)
{
	//char *str ="      echo    ' $sd ' >>  myfile$USER  < newfile _$USER #ggh\' asdf";
	char *str ="      echo   \"asd  11\"  '2b2m2'";

	initstruct();// инициализируем все поля в структуре
	printf("mainStr = %s\n", str);
		//while (*argv)
		//{
			//command_pre_parser(str);
			str = command_parser(str, env);
			//printf("%s", str);
			//printf("%s", str);
		//}





}
