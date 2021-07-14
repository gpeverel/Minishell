#include "minishell.h"



void	handle_signals(void)
{
	//if (!g_flag)
	//{// для работы с дочерними процессами
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_replace_line("",0);
		write(1, "\n", 1);
		rl_redisplay();
	//}
	//else
		//write(1, "\n", 1);
}

void	quit_signals(void)
{
	//if (!g_flag)
	//{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\b\b", 2);
	//}
	//else
	//	write(1, "Quit\n", 1);
}
