#include "minishell.h"

void	left_two_redir_str_push(char *str, int fd, t_env *my_env)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$')
		{
			str = pars_dollar(str, &i, my_env);
			continue ;
		}
		i++;
	}
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

void	work_left_two_redir(t_env *my_env)
{
	int		fd;
	char	*str;

	fd = open("<<", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	all.flag_red = 1;
	all.notfile = 0;
	while (1)
	{
		str = readline ("> ");
		if (!ft_strcmp(str, all.a_last->item))
		{
			free(str);
			break ;
		}
		if (str && *str)
			left_two_redir_str_push(str, fd, my_env);
		if (str == NULL)
		{
			all.notfile = 1;
			break ;
		}
	}
	all.flag_red = 0;
	close(fd);
}
