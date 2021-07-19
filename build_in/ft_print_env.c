#include "../minishell.h"

void 	ft_print_content(char *str, int fd)
{
	write(fd, "\"", 1);
	write(fd, str, ft_strlen(str));
	write(fd, "\"\n", 2);
}

void 	ft_print_key(char *str, int fd)
{
	char	*prefix;
	char	*posfix;

	prefix = "declare -x ";
	posfix = "=";
	write(fd, prefix, ft_strlen(prefix));
	write(fd, str, ft_strlen(str));
	write(fd, posfix, ft_strlen(posfix));
}

void 	ft_print_content_env(char *str, int fd)
{
	if (str != NULL)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

void 	ft_print_key_env(char *str, int fd)
{
	char	*posfix;

	posfix = "=";
	write(fd, str, ft_strlen(str));
	write(fd, posfix, ft_strlen(posfix));
}

void 	ft_print_myenv(int fd, t_env *my_env, int i)
{
	void	(*f_key)(char *, int);
	void	(*f_con)(char *, int);

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
	f(my_env, f_key, f_con, fd);
	all.error = 0;
}
