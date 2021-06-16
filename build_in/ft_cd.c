#include "../minishell.h"

int	ft_cd(char *path)
{
	if (path == NULL)
		printf("missing arguments");
	else
	{
		if (chdir(path) == -1)
			printf("error cd: %s\n", strerror(errno));
		printf("%s\n", path);
	}
	return (0);
}
