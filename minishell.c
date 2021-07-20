#include "minishell.h"

char	*ft_error(char *err)
{
	printf("%s\n", err);
	return (NULL);
}

char	*pars_bucket(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(str);
	free(tmp2);
	free(tmp3);
	(*i) -= 1;
	return (tmp);
}

char	*pars_double_bucket(char *str, int *i, t_env *my_env)
{
	char	*tmp;
	int		j;

	j = *i;
	++(*i);
	while (str[(*i)])
	{
		if (str[*i] == '$')
		{
			str = pars_dollar(str, i, my_env);
			continue ;
		}
		if (str[*i] == '\"')
			break ;
		++(*i);
	}
	tmp = join_str_bucket(str, i, j);
	return (tmp);
}

char	*command_parser(char *str, t_env *my_env)
{
	int		i;
	int		check_start_arg;
	char	*arg;

	i = 0;
	check_start_arg = -1;
	if (str[i] == ' ' && i == 0)
		str = delete_space(str, &i);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		g_all.check_dol = 0;
		check_start_arg = i;
		str = check_main_symbols_str(str, &i, my_env);
		if (g_all.check_dol != 1)
		{
			arg = init_arg(str, check_start_arg, i);
			push_elem(arg);
		}
	}
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	int		fd;
	t_env	*my_env;

	(void)argc;
	(void)argv;
	g_all.error = 0;
	my_env = ft_create_my_env(env, NULL);
	get_history_from_file();
	fd = open("fhistory", O_WRONLY | O_APPEND, 0644);
	while (1)
	{
		if (!main_loop_line(fd, my_env))
			break ;
	}
	close(fd);
	ft_lstclear_env(&my_env);
	return (0);
}
