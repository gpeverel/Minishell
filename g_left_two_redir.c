#include "minishell.h"

void	work_left_two_redir(t_env *my_env)
{
	int		fd;
	int		i;
	int		len;
	char	*str;

	fd = open("<<", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	all.flag = 1;
	all.notfile = 0;
	while (1)
	{
		i = 0;
		//signal(SIGQUIT, (void *)quit_signals);
		//signal(SIGINT, (void *)handle_signals);
		str = readline ("> ");
		if (!ft_strcmp(str, all.a_last->item))
		{
			free(str);
			break ;
		}
		if (str && *str)
		{
			len = ft_strlen(str);
			while (i < len)
			{
				if (str[i] == '$')
				{
					str = pars_dollar(str, &i, my_env);
					//printf("");
					continue ;
				}
				i++;
			}
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			free(str);
		}
		if (str == NULL)
		{
			all.notfile = 1;
			break ;
		}
	}
	all.flag = 0;
	close(fd);


}


