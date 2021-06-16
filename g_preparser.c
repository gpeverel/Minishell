#include "minishell.h"

void	command_pre_parser(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		i++;
	}
}