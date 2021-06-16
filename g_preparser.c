#include "minishell.h"

void	redir_add_list(count)
{


}

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
		if (str[i] == '>')
			redir_add_list(count);

		i++;
	}
}