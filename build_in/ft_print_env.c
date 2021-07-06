#include "../minishell.h"

void 	ft_print_content(char *str)
{
	write(1, "\"", 1);
	write(1, str, ft_strlen(str));
	write(1, "\"", 1);
	write(1, "\n", 1);
}

void 	ft_print_key(char *str)
{
	//printf("declare -x");
	write(1, "declare -x ", 11);
	write(1, str, ft_strlen(str));
	write(1, "=", 1);
}

void 	ft_print_myenv(t_env *my_env)
{
	void (*f_key)(char *);
	void (*f_con)(char *);

	f_key = &ft_print_key;
	f_con = &ft_print_content;
	ft_lstiter_env(my_env, f_key, f_con);
}
