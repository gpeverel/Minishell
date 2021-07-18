#include "../minishell.h"

void	ft_update_env(t_env *my_env, char **content, char *old_pwd)
{
	content = ft_find_env(my_env, "OLDPWD");
	free(*content);
	*content = old_pwd;
	content = ft_find_env(my_env, "PWD");
	free(*content);
	*content = getcwd(NULL, 0);
	all.error = 0;
}

int	ft_cd(t_env	*my_env, char *path)
{
	char	*path_final;
	char	**home;
	char	**content;
	char	*old_pwd;

	content = NULL;
	home = ft_find_env(my_env, "HOME");
	path_final = path;
	old_pwd = getcwd(NULL, 0);
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		path_final = *home;
	if (chdir(path_final) == -1)
	{
		free(old_pwd);
		all.error = 1;
		printf("cd: %s: No such file or directory\n", path_final);
	}
	else
		ft_update_env(my_env, content, old_pwd);
	return (0);
}
