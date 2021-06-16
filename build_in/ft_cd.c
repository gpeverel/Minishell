#include "../minishell.h"

int	ft_cd(char *path, char *home)
{
	char	*path_final;

	path_final = path;
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		path_final = home;
	if (chdir(path_final) == -1)
		printf("error cd: %s\n", strerror(errno));
	printf("%s\n", path_final);
	return (0);
}
