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

	if ((*fd) != 0)
		close(*fd);
	file = temp->item;
	if (temp->type == '1')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp->type == '2')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

void	ft_reddir_l(t_arg *temp, int *fd, int *flag)
{
	char	*file;

	if ((*fd) != 1)
		close(*fd);
	file = temp->item;
	if (temp->type == '3')
	{
		(*fd) = open(file, O_RDONLY, 0222);
		if ((*fd) < 0)
		{
			g_all.error = 1;
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
			g_all.error = 1;
			printf("%s: Error <<\n", file);
		}
	}
}

char	**ft_args(int i, t_arg *arr)
{
	char	**args;
	int		n;

	n = 0;
	args = malloc(sizeof(char *) * (i + 1));
	while (n < i)
	{
		if (arr->type != '1' && arr->type != '2' && arr->type != '3'
			&& arr->type != '4')
		{
			args[n] = arr->item;
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

	i++;
	args = ft_args(i, arr);
	ft_switcher(fd, args, my_env);
	if (fd[1] != 1)
		close(fd[1]);
	if (fd[0] != 0)
		close(fd[0]);
	free(args);
	return (i);
}
