#include "minishell.h"

char	*ft_strnewcpy(char *str, int size)
{
	char	*tmp;
	int		len;

	if (str != NULL)
	{
		len = ft_strlen(str);
		if (len < size)
			size = len;
		tmp = malloc(sizeof(char) * size + 1);
		tmp[size] = '\0';
		while (--size != -1)
		{
			tmp[size] = str[size];
		}
		return (tmp);
	}
	return (NULL);
}

void	push_redir(char *str, int i, char *filename)
{
	t_arg	*tmp;

	tmp = malloc(sizeof(t_arg));
	if (str[i] == '>' && str[i + 1] == '>')
		tmp->type = '2';
	else if (str[i] == '>' && str[i + 1] != '>')
		tmp->type = '1';
	else if (str[i] == '<' && str[i + 1] == '<')
		tmp->type = '4';
	else if (str[i] == '<' && str[i + 1] != '<')
		tmp->type = '3';
	tmp->item = filename;
	tmp->next = NULL;
	if (all.a_last == NULL)
	{
		//tmp->next = tmp;
		all.a_last = tmp;
		all.a_first = tmp;
		all.a_last->next = NULL;
	}
	else
	{
		//tmp->next = all.a_first;
		all.a_last->next = tmp;
		all.a_last = tmp;
	}
}

int	check_main_symb(char **str, int *j, t_env *my_env)
{
	if ((*str)[*j] == '\'')
	{
		(*str) = pars_bucket((*str), j);
		if ((*str)[*j] == '\'' || (*str)[*j] == '\"')
			return (1);
	}
	if ((*str)[*j] == '\"')
	{
		(*str) = pars_double_bucket((*str), j, my_env);
		if ((*str)[*j] == '\'' || (*str)[*j] == '\"')
			return (1);
	}
	if ((*str)[*j] == '$')
	{
		(*str) = pars_dollar((*str), j, my_env);
		if ((*str)[*j] == '\'' || (*str)[*j] == '\"' || (*str)[*j] == '$')
			return (1);
	}
	if ((*str)[*j] == ' ' || (*str)[*j] == '\t' || (*str)[*j] == '\0' ||
		(*str)[*j] == '>' || (*str)[*j] == '<')
		return (2);
	return (0);
}

void	redir_go_check_line(char **str, int *j, t_env *my_env)
{
	int	check;

	check = 0;
	while (str[*j])
	{
		check = check_main_symb(str, j, my_env);
		if (check == 1)
			continue ;
		else if (check == 2)
			break ;
		(*j)++;
	}
}

char	*pars_redir_one(char *str, int *i, t_env *my_env)
{
	int		j;
	int		z;
	char	*tmp;

	j = *i + 1;
	//if (str[*i + 1] == '<' )
	//	return(work_left_two_redir(&str));
	if (str[*i + 1] == '>' || str[*i + 1] == '<')
		j++;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	//printf("%d\n", j);
	z = j;
	redir_go_check_line(&str, &j, my_env);
	push_redir(str, *i, ft_strnewcpy(str + z, j - z));// пихаем в структуру
	if (all.a_last->type == '4')
		work_left_two_redir(my_env);// для <<
	tmp = ft_substr_g(str, 0, *i - 1);
	tmp = ft_strjoin(tmp, str + j);
	if ((str[j] == '\0' || str[*i] == '<' || str[*i] == '>') && *i != 0)
		(*i)--;// если редирект в конце команды, чтобы не вых за грань, или если редирек за редиректом
	//printf("%d\n", j);
	free(str);
	all.check_dol = 1;
	return (tmp);
}
