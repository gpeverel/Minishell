#include "../minishell.h"

int	ft_switcher(int *fd, char **args, t_env *my_env)
{
	pid_t	pid;

	if (args[0] == NULL)
		return (0);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(my_env, args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd[1], &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd[1]);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(fd[1], my_env, &args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_print_myenv(fd[1], my_env, 0);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(my_env, &args[1]);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(&args[1]);
	else
		fr_exec(fd, my_env, args, pid);
	return (1);
}

void	ft_reddir_r(t_arg *temp, int *fd)
{
	char	*file;

	//printf("00\n");
	//printf("type=%c, item=%s\n", temp->type, temp->item);
	file = temp->item;
	printf("file=%s\n", file);
	if (temp->type == '1')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp->type == '2')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	printf("fd=%d\n", (*fd));
}

void	ft_reddir_l(t_arg *temp, int *fd, int *flag)
{
	char	*file;

	//printf("type=%c, item=%s\n", temp->type, temp->item);
	file = temp->item;
	//printf("file=%s\n", file);
	if (temp->type == '3')
	{
		(*fd) = open(file, O_RDONLY, 0222);
		if ((*fd) < 0)
		{
			all.error = 1;
			printf("%s: No such file or directory\n", file);
			*flag = 1;
			(*fd) = 0;
		}
	}
	if (temp->type == '4')
	{
		(*fd) = open("<<", O_RDONLY, 0222);
		if ((*fd) < 0)
		{
			all.error = 1;
			printf("%s: Error <<\n", file);
			*flag = 1;
			(*fd) = 0;
		}
	}
	printf("fd=%d\n", (*fd));
}

char	**ft_args(int i, t_arg *arr)
{
	char **args;
	int	n;

	n = 0;
	args = malloc(sizeof(char *) * (i + 1));
	while (n < i)
	{
		if (arr->type != '1' && arr->type != '2' && arr->type != '3'
			&& arr->type != '4')
		{
			args[n] = arr->item;
			printf("args[n]=%s\n", args[n]);
			n++;
		}
		arr = arr->next;
	}
	args[n] = NULL;
	return (args);
}

int	getExec(t_env *my_env, int i, int *fd, t_arg *arr)
{
	char	**args;

	//printf("2type=%c, item=%s\n", temp->type, temp->item);
	i++;
	//printf("11\n");
	//printf("type=%c, item=%s\n", temp->type, temp->item);
	//printf("i=%d\n", i);
	args = ft_args(i, arr);
	ft_switcher(fd, args, my_env);
	if (fd[1] != 1)
		close(fd[1]);
	if (fd[0] != 0)
		close(fd[0]);
	free(args);
	return (i);
}

void	ft_pipe(t_env *my_env, int i, t_arg *arr, int *fd_old)
{
	int		fd[2];
	pid_t	pid;
	char	*path;
	char	**env;
	int		status;
	char	**args;

	args = ft_args(i, arr);
	pipe(fd);
	path = ft_get_path(my_env, args[0]);
	if (path == NULL)
		return ;
	printf("path=%s\n", path);
	env = ft_create_env_arr(my_env);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve(path, args, env);
		close(fd[1]);
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
		all.error = 1;
		printf("error: fork\n");
	}
	ft_free_arr(env);
	free(path);
	free(args);
}

int	ft_adapter(t_env *my_env)
{
	t_arg	*temp;
	int		i;
	int		flag;
	int		fd[2];
	t_arg	*arr;

	i = 0;
	fd[0] = 0;
	fd[1] = 1;
	flag = 0;
	temp = all.a_first;
	arr = temp;
	while (temp)
	{
		//printf("type=%c, item=%s\n", temp->type, temp->item);
		if (temp->type == '1' || temp->type == '2')
		{
			//printf("1type=%c, item=%s\n", temp->type, temp->item);
			ft_reddir_r(temp, &fd[1]);
			i--;
		}
		if (temp->type == '3' || temp->type == '4')
		{
			//printf("3type=%c, item=%s\n", temp->type, temp->item);
			ft_reddir_l(temp, &fd[0], &flag);
			i--;
		}
		if (temp->type == 'p')
		{
			all.pipe_on = 1;
			//printf("1p_type=%c, item=%s\n", temp->type, temp->item);
			temp = temp->next;
			//printf("2p_type=%c, item=%s\n", temp->type, temp->item);
			ft_pipe(my_env, i, arr, fd);
			i = 0;
			arr = temp;
		}
		if (temp->next == NULL && flag == 0)
		{
			i = getExec(my_env, i, fd, arr);
		}
		i++;
		//printf("i=%d\n", i);
		temp = temp->next;
	}
	return (0);
}
