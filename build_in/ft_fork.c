#include "../minishell.h"
#include <unistd.h>
#include <sys/stat.h>

char *ft_path_command(char *path, char *command)
{
    char *temp;
    char *temp1;

    temp = ft_strjoin(path, "/");
    temp1 = ft_strjoin(temp, command);
    return (temp1);
}

char	*ft_check_path(t_env *my_env, char *arg)
{
	char	*path;
	char	*path_end;
	char	**paths_arr;
	int i;
	struct stat buf;

	i = 0;
    path_end = NULL;
    paths_arr = ft_split(*ft_find_env(my_env, "PATH"), ':');
    while (paths_arr[i] != NULL)
    {
        path = ft_path_command(paths_arr[i], arg);
        if (stat(path, &buf) != 0)
        {
            free(path);
            path = NULL;
            errno = 0;
        }
        else
            path_end = path;
        i++;
    }
    free(paths_arr);
    return (path_end);
}

char    *ft_strcat(char *dst, char *src, char *three)
{
    int	i;
    int	j;
    int	len;
    char *str;

    i = 0;
    j = 0;
    len = ft_strlen(dst) + ft_strlen(src) + ft_strlen(three);
    str = malloc(len + 1);
    while (dst[j] != '\0')
        str[i++] = dst[j++];
    j = 0;
    while (src[j] != '\0')
        str[i++] = src[j++];
    j = 0;
    while (three[j] != '\0')
        str[i++] = three[j++];
    str[i] = '\0';
    return (str);
}

char **ft_create_env_arr(t_env *my_env)
{
    int i;
    int size;
    char **env;
    t_env *temp;

    i = 0;
    size = ft_lstsize_env(my_env);
    env = malloc(sizeof (char **) * (size + 1));
    temp = my_env;
    while(temp != NULL)
    {
        env[i] = ft_strcat(temp->key, "=", temp->content);
        temp = temp->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

void ft_free_arr(char **env)
{
    int i;

    i = 0;
    while(env[i] != NULL)
    {
        free(env[i]);
        env[i] = NULL;
        i++;
    }
    free(env);
    env = NULL;
}

void fr_exec(t_env *my_env, char **args)
{
	pid_t	pid;
	char	*path;
	char	**env;
    int		status;

    path = ft_check_path(my_env, args[0]);
    if (path == NULL)
    {
        errno = 127;
        printf("%s: command not found\n", args[0]);
		return;
    }
    env = ft_create_env_arr(my_env);
    pid = fork();
    if (pid == 0)
        execve(path, args, env);
    else if (pid > 0)
        wait(&status);
    else
    {
        errno = 1;
        printf("error: fork\n");
    }
    ft_free_arr(env);
    free(path);
}