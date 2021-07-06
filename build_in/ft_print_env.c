#include "../minishell.h"

void 	ft_print_content(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void 	ft_print_key(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, " = ", 3);
}

void 	ft_print_myenv(t_env *my_env)
{
	void (*f_key)(char *);
	void (*f_con)(char *);

	f_key = &ft_print_key;
	f_con = &ft_print_content;
	ft_lstiter_env(my_env, f_key, f_con);
}
