#include "minishell.h"

int		backet_check(char *str, int buck, int *place, char c)
{
	while (str[++(*place)])
	{
		if (str[*place] == c && buck == 1)
		{
			buck = 0;// ковычки закрылись
			break;
		}
		//if (str[*place] == c && buck == 0)
		//{
		//	buck = 1;// ковычки открылись
		//}
	}
	return (buck);
}

char	*recalcul_backet(char *str)
{
	int	one_buck;
	int	two_buck;
	int	i;

	i = 0;
	one_buck = 0;
	two_buck = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			one_buck = backet_check(str, ++one_buck, &i, '\'');
			if (one_buck == 1)
				return(ft_error("Не закрыта одинарная ковычка!"));
		}
		if (str[i] == '\"')
		{
			two_buck = backet_check(str, ++two_buck, &i, '\"');
			if (two_buck == 1)
				return (ft_error("Не закрыта двойная ковычка!"));
		}
		i++;
	}
	return ("+");
}

int		command_pre_parser(char *str)
{
	int i;
	int	count;

	if (recalcul_backet(str) == NULL)
		return (-1);
	if (redir_pre_pars(str) == NULL)
		return (-1);
	return (0);
}