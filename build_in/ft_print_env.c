#include "../minishell.h"

void 	ft_print_content(char *str)
{
	printf("\"%s\"\n", str);
	/*write(1, "\"", 1);
	write(1, str, ft_strlen(str));
	write(1, "\"", 1);
	write(1, "\n", 1);*/
}

void 	ft_print_key(char *str)
{
	char *prefix;
	char *posfix;

	prefix = "declare -x ";
	posfix = "=";
	//printf("declare -x %s =", str);
	write(1, prefix, ft_strlen(prefix));
	write(1, str, ft_strlen(str));
	write(1, posfix, ft_strlen(posfix));
}


void 	ft_print_content_env(char *str)
{
	printf("%s\n", str);
	/*write(1, "\"", 1);
	write(1, str, ft_strlen(str));
	write(1, "\"", 1);
	write(1, "\n", 1);*/
}

void 	ft_print_key_env(char *str)
{
	char *posfix;

	posfix = "=";
	//printf("declare -x %s =", str);
	write(1, str, ft_strlen(str));
	write(1, posfix, ft_strlen(posfix));
}

void 	ft_print_myenv(t_env *my_env, int i)
{
	void (*f_key)(char *);
	void (*f_con)(char *);

	if (i != 0)
	{
		f_key = &ft_print_key;
		f_con = &ft_print_content;
	}
	else
	{
		f_key = &ft_print_key_env;
		f_con = &ft_print_content_env;
	}
	ft_lstiter_env(my_env, f_key, f_con);
}