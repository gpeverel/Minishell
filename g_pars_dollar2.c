#include "minishell.h"

void	while_key_end(int *i, char *str)
{
	while (str[++(*i)])
	{
		if (str[(*i)] == '?')
		{
			(*i)++;
			break ;
		}
		if (!ifkey(str[*i]))
			break ;
	}
}

void	if_str_null(char **tmp2, char *str, int *i)
{
	(*tmp2) = ft_strdup(str + *i);
	if (g_all.check_dol != 2)
		g_all.check_dol = 1;
}

char	*join_all_part(char **key, char *tmp2, char *str)
{
	*key = ft_strjoin(*key, tmp2);
	free(tmp2);
	free(str);
	return (*key);
}

int	check_pipe_in_str(char *str, int *i)
{
	if (str[*i] == '|' && (g_all.check_dol == 2 || g_all.check_dol == 1))
		return (1);
	else if (str[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}
