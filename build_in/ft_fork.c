#include "../minishell.h"
#include <sys/types.h>
#include <unistd.h>

void ft_child(t_env *my_env)
{

}

void ft_parent(t_env *my_env, pid_t pid)
{

}

void ft_fork(t_env *my_env, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		errno = 1;
		printf("error: fork\n");
	}
	if (pid == 0)
		ft_child(my_env);
	if (pid > 0)
		ft_parent(my_env, pid);
}