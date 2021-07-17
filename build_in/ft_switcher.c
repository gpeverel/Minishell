#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	if (src1 == NULL || src2 == NULL)
		return (-1);
	while (src1[i] != '\0' || src2[i] != '\0')
	{
		if (src1[i] == '\0' && src2[i] == '\0')
			return (0);
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}

char	**ft_find_env(t_env *my_env, char *key)
{
	size_t	len;

	while (my_env != NULL)
	{
		len = ft_strlen(my_env->key);
		if (ft_strncmp(my_env->key, key, len) == 0)
		{
			return (&my_env->content);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

int	ft_switcher(int fd, char **args, t_env	*my_env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(my_env, args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd, &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(fd, my_env, &args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_print_myenv(fd, my_env, 0);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(my_env, &args[1]);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(&args[1]);
	else
		fr_exec(my_env, args);
	return (0);
}

void ft_double_redirect(t_env *my_env)
{
	char 	**args;


	args = malloc(sizeof(char *) * 3);
	args[0] = "cat";
	args[1] = "<<";
	args[2] = NULL;
	ft_switcher(1, args, my_env);
	free(args);
}

void ft_reddir_r(t_arg *temp, int *fd)
{
	char	*file;

	//printf("00\n");
	//printf("type=%c, item=%s\n", temp->type, temp->item);
	file = temp->item;
	//printf("file=%s\n", file);
	if (temp->type == '1')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp->type == '2')
		(*fd) = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	//printf("fd=%d\n", (*fd));
}

int ft_adapter(t_env *my_env)
{
	char 	**args;
	t_arg	*temp;
	int 	i;
	int 	n;
	int 	fd;
	t_arg	*arr;

	i = 0;
	fd = 1;
	temp = all.a_first;
	arr = temp;
printf(">> begin <<\n\n");
//printf("type=%c, item=%s\n", temp->type, temp->item);
		if (temp->type == '1')
		{
			ft_reddir_r(temp, &fd);
			i--;
		}
		if (temp->next == all.a_first)
		{
			i++;
			printf("1\n");
			printf("type=%c, item=%s\n", temp->type, temp->item);
			printf("i=%d\n", i);
			args = malloc(sizeof(char *) * (i + 1));
			n = 0;
			while (n < i)
			{
				if (arr->type != '1')
				{
					args[n] = arr->item;
					printf("args[n]=%s\n", args[n]);
					n++;
				}
				arr = arr->next;
			}
			args[n] = NULL;
			ft_switcher(fd, args, my_env);
			close(fd);
			free(args);
		}
		i++;
	printf("i=%d\n", i);
	temp = temp->next;
	while (temp != all.a_first)
	{
		if (temp->type == '1' || temp->type == '2')
		{
			ft_reddir_r(temp, &fd);
			i--;
		}
		if (temp->next == all.a_first)
		{
			i++;
			printf("11\n");
			printf("type=%c, item=%s\n", temp->type, temp->item);
			printf("i=%d\n", i);
			args = malloc(sizeof(char *) * (i + 1));
			n = 0;
			while (n < i)
			{
				if (arr->type != '1')
				{
					args[n] = arr->item;
					printf("args[n]=%s\n", args[n]);
					n++;
				}
				arr = arr->next;
			}
			args[n] = NULL;
			ft_switcher(fd, args, my_env);
			if(fd != 1)
				close(fd);
			free(args);
		}
		i++;
		printf("i=%d\n", i);
		temp = temp->next;
	}
	//while (1);
	return 0;
}
