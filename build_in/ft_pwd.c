#include "../minishell.h"
#include <unistd.h>

int	ft_pwd()
{
	char *buf;

	buf = NULL;
	printf("%s\n", getcwd(buf, 0));
	return (0);
}