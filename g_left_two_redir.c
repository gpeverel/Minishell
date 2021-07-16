#include "minishell.h"

void	work_left_two_redir(void)
{
	int		fd;
	char	*str;

	fd = open("<<", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	all.flag = 1;
	while (1)
	{
		str = readline ("> ");
		if (!ft_strcmp(str, all.a_last->item))
			break ;
		if (str && *str)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			free(str);
		}
	}
	all.flag = 0;
	close(fd);


}


