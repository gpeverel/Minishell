#include "../minishell.h"

int	ft_pwd(int fd)
{
	char	*buf;

	buf = NULL;
	write(fd, getcwd(buf, 0), ft_strlen(getcwd(buf, 0)));
	write(fd, "\n", 1);
	///printf("%s\n", getcwd(buf, 0));
	return (0);
}
