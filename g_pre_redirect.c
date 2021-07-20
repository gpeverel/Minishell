#include "minishell.h"

int	skip_first_redir(char *str, int i, char fir, char sec)
{
	i++;
	if (str[i] == fir)
		i++;
	if (str[i] == sec)
	{
		ft_error("Редирект не в ту сторону!");
		return (-1);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		ft_error("Нет названия файла для редиректа!");
		return (-1);
	}
	return (i);
}

char	*skip_clear_filename(char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (str[*i] == '<' || str[*i] == '>')
			return (ft_error("Редирект без отступа!"));
		(*i)++;
	}
	if (str[*i] == '<' || str[*i] == '>')
		return (ft_error("Лишний редирект!"));
	return ("+");
}

char	*redir_pre_side(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		if (str[*i] == '\'' && str[*i + 1] == '\'')
			return (ft_error("Пустое название файла для редиректа!"));
		while (str[*i] != '\'')
			(*i)++;
		return ("+");
	}
	else if (str[*i] == '\"')
	{
		if (str[*i] == '\"' && str[*i + 1] == '\"')
			return (ft_error("Пустое название файла для редиректа!"));
		while (str[*i] != '\"')
			(*i)++;
		return ("+");
	}
	else
		if (skip_clear_filename(str, i) == NULL)
			return (NULL);
	return ("+");
}

char	*redir_pre_pars(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>')
				i = skip_first_redir(str, i, '>', '<');
			else if (str[i] == '<')
				i = skip_first_redir(str, i, '<', '>');
			if (i == -1)
				return (NULL);
			ret = redir_pre_side(str, &i);
			if (ret == NULL)
				return (NULL);
			else
				continue ;
		}
	}
	return ("+");
}
