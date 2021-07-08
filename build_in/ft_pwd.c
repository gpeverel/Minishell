#include "../minishell.h"

int	ft_pwd(int fd)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 0);
	write(fd, pwd, ft_strlen(pwd));
	free(pwd);
	return (0);
}
