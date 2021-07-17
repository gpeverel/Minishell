#include "minishell.h"



void	handle_signals(void)
{
	if (!all.flag)
	{// для работы с дочерними процессами
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 1);
		write(1, "> ", 2);
	}
}

void	quit_signals(void)
{
	if (!all.flag)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\b\b", 2);
	}
	else
	{
		write(1, "\n", 1);
		write(1, "> ", 2);
	// 	//rl_replace_line("",0);
	// 	//all.break_f = 1;
	}
}

void	if_there_is_str(int fd, char *str, t_env *my_env)
{
	int	i;

	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	add_history(str);
	i = command_pre_parser(str);
	if (i != -1)
	{
		str = command_parser(str, my_env);
		ft_adapter(my_env);
	}
	else
		all.error = 258;
	free(str);
	del_all_pars_list();
}

int		main_loop_line(int fd, t_env *my_env)
{
	char	*str;

	initstruct();
	signal(SIGINT, (void *)handle_signals);
	signal(SIGQUIT, (void *)quit_signals);
	str = readline ("write: ");
	if (str == NULL)
	{
		write(1, "\e[A\e[D", 6);
		write(1, "write: exit\n", 12);
		write(fd, "exit\n", 5);
		del_all_pars_list();
		return (0);
	}
	if (str && *str)
	{
		if_there_is_str(fd, str, my_env);
		// write(fd, str, ft_strlen(str));
		// write(fd, "\n", 1);
		// add_history(str);
		// i = command_pre_parser(str);
		// if (i != -1)
		// 	str = command_parser(str, my_env);
		// ft_adapter(my_env);
		// free(str);
		// del_all_pars_list();
	}
	return (1);
}