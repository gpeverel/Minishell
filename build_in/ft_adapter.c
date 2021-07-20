#include "../minishell.h"

void	ft_pid_fork(int *fd, char *path, char **env, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(path, args, env);
	}
	else if (pid > 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(&status);
		close(fd[0]);
	}
	else
	{
		g_all.error = 1;
		printf("error: fork\n");
	}
	g_all.error = WEXITSTATUS(status);
}

void	ft_pipe(t_env *my_env, int i, t_arg *arr, int *fd_old)
{
	int		fd[2];
	char	*path;
	char	**env;
	char	**args;

	args = ft_args(i, arr);
	pipe(fd);
	path = ft_get_path(my_env, args[0]);
	if (path == NULL)
		return ;
	env = ft_create_env_arr(my_env);
	ft_pid_fork(fd, path, env, args);
	ft_free_arr(env);
	free(path);
	free(args);
}

void	ft_check_reddir(t_arg *temp, int *fd, int *i, int *flag)
{
	if (temp->type == '1' || temp->type == '2')
	{
		ft_reddir_r(temp, &fd[1]);
		(*i)--;
	}
	if (temp->type == '3' || temp->type == '4')
	{
		ft_reddir_l(temp, &fd[0], flag);
		(*i)--;
	}
}

void	ft_check_type(t_env *my_env, t_arg *temp, int *fd, t_arg *arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (temp)
	{
		ft_check_reddir(temp, fd, &i, &flag);
		if (temp->type == 'p')
		{
			g_all.pipe_on = 1;
			temp = temp->next;
			ft_pipe(my_env, i, arr, fd);
			i = 0;
			arr = temp;
		}
		if (temp->next == NULL && flag == 0)
			i = getExec(my_env, i, fd, arr);
		i++;
		temp = temp->next;
	}
}

int	ft_adapter(t_env *my_env)
{
	t_arg	*temp;
	int		fd[2];
	t_arg	*arr;
	int		fd_old[2];

	fd[0] = 0;
	fd[1] = 1;
	fd_old[0] = dup(0);
	fd_old[1] = dup(1);
	temp = g_all.a_first;
	arr = temp;
	ft_check_type(my_env, temp, fd, arr);
	dup2(fd_old[0], 0);
	dup2(fd_old[1], 1);
	close(fd_old[0]);
	close(fd_old[1]);
	return (0);
}
