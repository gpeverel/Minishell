#include "../minishell.h"

int	ft_cd(char *path, char *home)
{
	char	*path_final;

	path_final = path;
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		path_final = home;
	if (chdir(path_final) == -1)
		printf("error cd: %s\n", strerror(errno));
	ft_pwd(1);
	//todo: удалить при выкате на прод
	return (0);
}
