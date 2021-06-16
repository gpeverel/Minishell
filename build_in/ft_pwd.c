#include "../minishell.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	printf("%s\n", getcwd(buf, 0));
	return (0);
}
