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
	while (str[++(*i)])
	{
		//if (str[*i] == '\\' && (str[*i + 1] == '\"'
		// || str[*i + 1] == '$' || str[*i + 1] == '\\'))
		//	str = pars_slesh(str, i);
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

// char	*pars_slesh(char *str, int *i)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	tmp = ft_substr(str, 0, *i);
// 	(*i)++;
// 	if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '\\' ||
// 	 str[*i] == '\t'/* || str[*i] == '\'*/ || str[*i] == '\n')
// 		tmp2 = ft_strdup(str + *i);
// 	else
// 		tmp2 = ft_strdup(str + *i + 1);
// 	tmp = ft_strjoin(tmp, tmp2);
// 	free(str);
// 	free(tmp2);
// 	(*i)++;
// 	return(tmp);
// }

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

int		check_start_arg_space(char **str, int *start)
{
	if (all.check_dol == 1 && !*str[*start])
	{
		*str = delete_space(*str, start);
		(*start)++;
		all.check_dol = 0;
		return (1);
	}
	return (0);
}

int		check_arg_end(char **str, int *start)
{
	if (all.check_dol == 1)
	{
		*str = delete_space(*str, start);
		if(!*str[*start])
			(*start)++;
		all.check_dol = 0;
		return (1);
	}
	return (0);
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
		check_start_arg = i;
		str = check_main_symbols_str(str, &i, env);
		//printf("c = %c|\n", str[i]);
		//if (check_start_arg_space(&str, &i))
			//continue;
		while (1) // 1 чтобы решить проблему с концом строки
		{
			if ((str[i] == ' ' || str[i + 1] == '\0')
			 || str[i] == '<' || str[i] == '>')// очень опасно i + 1
			{
				//if (str[i] == '<' || str[i] == '>')// защита от слипания
				//	i--;// 						простых символов и <>
				if (check_arg_end(&str, &i))
				{
					i++;
					break;
				}
				arg = init_arg(str, check_start_arg, i);
				push_elem(arg);
				str = delete_space(str, &i);
				if (*arg)// пиздец что это блять
					i++;
				if (str[i - 1] == '<' || str[i - 1] == '>')// защита от слипания
					i--;// 						простых символов и <>
				//while (str[i] == ' ')// ты ебанулся что ли так делать
				//	i++;
				printf("\n|%s|\n", arg);
				break;
			}
			i++;
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
	//char *str ="      echo    ' $sd ' >>  myfile$USER  < newfile _$USER #ggh\' asdf";
	char *str1 = "   \'ASD\'\"QWE\">    123   $MY\"asd      15\"'1b2m3'";
	len = ft_strlen(str1);
	char *str = malloc(len + 1);

	while (i < len)
	{
		str[i] = str1[i];
		i++;
	}
	str[i] = '\0';
	initstruct();// инициализируем все поля в структуре
	printf("mainStr = %s|\n", str);
		//while (*argv)
		//{
			//command_pre_parser(str);
			str = command_parser(str, env);
			free(str);
			//printf("%s", str);
			//while (1)
			//{}





}
