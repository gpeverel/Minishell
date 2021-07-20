#include "../minishell.h"

char	*ft_check_path(t_env *my_env, char *arg, int i)
{
	char		*path;
	char		**path_test;
	char		*path_end;
	char		**paths_arr;
	struct stat	buf;

	path_end = NULL;
	path_test = ft_find_env(my_env, "PATH");
	if (path_test == NULL)
		return (NULL);
	paths_arr = ft_split(*path_test, ':');
	while (paths_arr[i] != NULL)
	{
		path = ft_path_command(paths_arr[i], arg);
		if (stat(path, &buf) != 0)
		{
			free(path);
			path = NULL;
		}
		else
			path_end = path;
		i++;
	}
	free(paths_arr);
	return (path_end);
}

char	**ft_create_env_arr(t_env *my_env)
{
	int		i;
	int		size;
	char	**env;
	t_env	*temp;

	i = 0;
	size = ft_lstsize_env(my_env);
	env = malloc(sizeof (char **) * (size + 1));
	temp = my_env;
	while (temp != NULL)
	{
		env[i] = ft_strcat(temp->key, "=", temp->content);
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_get_path(t_env *my_env, char *arg)
{
	char	*path;
	int		i;

	i = 0;
	if (arg[0] == '/' || arg[0] == '.')
		path = ft_strdup(arg);
	else
	{
		path = ft_check_path(my_env, arg, i);
		if (path == NULL)
		{
			all.error = 127;
			printf ("%s: command not found\n", arg);
		}
	}
	return (path);
}

void	fr_exec(int *fd, t_env *my_env, char **args)
{
	pid_t	pid;
	char	*path;
	char	**env;
	int		status;

	path = ft_get_path(my_env, args[0]);
	if (path == NULL)
		return ;
	env = ft_create_env_arr(my_env);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		execve(path, args, env);
	}
	else if (pid > 0)
		wait(&status);
	else
	{
		all.error = 1;
		printf("error: fork\n");
	}
	ft_free_arr(env);
	free(path);
	all.error = WEXITSTATUS(status);
}
