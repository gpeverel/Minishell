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
	g_all.flag_red = 1;
	g_all.notfile = 0;
	while (1)
	{
		str = readline ("> ");
		if (!ft_strcmp(str, g_all.a_last->item))
		{
			free(str);
			break ;
		}
		if (str && *str)
			left_two_redir_str_push(str, fd, my_env);
		if (str == NULL)
		{
			g_all.notfile = 1;
			break ;
		}
	}
	g_all.flag_red = 0;
	close(fd);
}

char	*prepars_pipe_errors(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
		return (ft_error("Ощибка синтаксиса!"));
	if (str[*i] == '\0')
		return (ft_error("Пайп в конце команды!"));
	if (str[*i] == '|')
		return (ft_error("Несколько пайпов сразу!"));
	return ("+");
}
