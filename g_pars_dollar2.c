#include "minishell.h"

void	while_key_end(int *i, char *str)
{
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
}

void	if_str_null(char **tmp2, char *str, int *i)
{
	(*tmp2) = ft_strdup(str + *i);// пропустили весь ключ
	if (all.check_dol != 2)// если перед $ были другие символы
		all.check_dol = 1;// чтобы нормально работать с пробелами при парсере
}

char	*join_all_part(char **key, char *tmp2, char *str)
{
	*key = ft_strjoin(*key, tmp2);
	free(tmp2);//printf("%s\n", key);
	free(str);
	return (*key);
}