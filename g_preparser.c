#include "minishell.h"



void	command_pre_parser(char *str)
{
	int i;
	int	count;
	all.red_count = 0;
	all.red_work = NULL;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			count++;

	}
}