#include "../minishell.h"

int	ft_cd(t_env	*my_env, char *path)
{
	char	*path_final;
	char	**home;
	char	**content;

	home = ft_find_env(my_env, "HOME");
	content = ft_find_env(my_env, "OLDPWD");
	free(*content);
	*content = getcwd(NULL, 0);
	path_final = path;
//printf("home=%s\n", *home);
//printf("oldpwd=%s\n", *content);

	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		path_final = *home;
	if (chdir(path_final) == -1)
		printf("error cd: %s\n", strerror(errno));

	content = ft_find_env(my_env, "PWD");
	free(*content);
	*content = getcwd(NULL, 0);
//printf("pwd=%s\n\n", *content);
//ft_pwd(1);
	//todo: удалить при выкате на прод
	return (0);
}
