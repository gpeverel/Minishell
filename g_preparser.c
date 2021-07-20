#include "minishell.h"

int	backet_check(char *str, int buck, int *place, char c)
{
	while (str[++(*place)])
	{
		if (str[*place] == c && buck == 1)
		{
			buck = 0;
			break ;
		}
	}
	return (buck);
}

char	*prepars_backet_check(char *str, int *i)
{
	int	one_buck;
	int	two_buck;

	one_buck = 0;
	two_buck = 0;
	if (str[*i] == '\'')
	{
		one_buck = backet_check(str, ++(one_buck), i, '\'');
		if (one_buck == 1)
			return (ft_error("Не закрыта одинарная ковычка!"));
	}
	if (str[*i] == '\"')
	{
		two_buck = backet_check(str, ++(two_buck), i, '\"');
		if (two_buck == 1)
			return (ft_error("Не закрыта двойная ковычка!"));
	}
	return ("+");
}

char	*recalcul_backet(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (prepars_backet_check(str, &i) == NULL)
				return (NULL);
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if (pipe_pre_pars(str, &i))
				continue ;
			else
				return (NULL);
		}
		i++;
	}
	return ("+");
}

char	*pipe_pre_pars(char *str, int *i)
{
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i])
	{
		if (str[(*i)] == '|' && (*i)++)
		{
			while (str[*i] == ' ')
				(*i)++;
			if (prepars_pipe_errors(str, i) == NULL)
				return (NULL);
			continue ;
		}
		if (str[*i] == '>' || str[*i] == '<')
		{
			while (str[*i] == '>' || str[*i] == '<')
				(*i)++;
			while (str[*i] == ' ')
				(*i)++;
			if (str[*i] == '|')
				return (ft_error(" Пайп в названии файла!"));
			continue ;
		}
		(*i)++;
	}
	return ("+");
}

int	command_pre_parser(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		ft_error("Пайп в начале команды!");
		return (-1);
	}
	if (recalcul_backet(str) == NULL)
		return (-1);
	if (redir_pre_pars(str) == NULL)
		return (-1);
	return (0);
}
