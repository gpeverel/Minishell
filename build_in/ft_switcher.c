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

int	ft_switcher(char **args, t_env	*my_env)
{
	int		fd;

	fd = 1;

	int n = 0;
/*	while (args[n] != NULL)
	{
		printf("arr: %s\n", args[n]);
		n++;
	}*/

//ft_print_myenv(my_env, 0);
//printf("\n\n");
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(my_env, args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd, &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(my_env, &args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_print_myenv(my_env, 0);
	else if (ft_strcmp(args[0], "unset") == 0)
		my_env = ft_unset(my_env, &args[1]);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(&args[1]);
	else
	{
		printf("no\n");
		//ft_fork(my_env, args);
	}
//ft_print_myenv(my_env, 0);
	return (0);
}

int ft_adapter(t_env *my_env)
{
	char 	**args;
	t_arg	*temp;
	int 	i;
	int 	n;
	t_arg	*arr;


	i = 0;
	temp = all.a_first;
	arr = temp;

printf(">> begin <<\n\n");
	do
	{
		/*while (temp != all.a_first && temp->type != 'p' && temp->type != '1' &&
		temp->type != '2' && temp->type != '3' && temp->type != '4')
		{
			temp = temp->next;
		}*/
		/*while (temp != all.a_first && (temp->type == 'c' || temp->type == 'a'))
		{
			i++;
			temp = temp->next;
		}*/

		if (temp->type == 'p' || temp->type == '1' ||
		   temp->type == '2' || temp->type == '3' || temp->type == '4')
		{
			//printf("type=%c, item=%s, i=%d\n", temp->type, temp->item, i);
			args = malloc(sizeof(char *) * (i + 1));
			n = 0;
			while (n < i)
			{
				args[n] = arr->item;
				//printf("arr->item=%s, n=%d\n", arr->item, n);
				arr = arr->next;
				n++;
			}
			args[n] = NULL;
			arr = temp;
/*
			n = 0;
			while (args[n] != NULL)
			{
				printf("arr: %s\n", args[n]);
				n++;
			}*/

			ft_switcher(args, my_env);
			i = 0;
			free(args);
		}
		if (temp->next == all.a_first)
		{
			i++;
			//printf("type=%c, item=%s, i=%d\n", temp->type, temp->item, i);
			args = malloc(sizeof(char *) * (i + 1));
			n = 0;
			while (n < i)
			{
				args[n] = arr->item;
				//printf("arr->item=%s, n=%d\n", arr->item, n);
				arr = arr->next;
				n++;
			}
			args[n] = NULL;
			arr = temp;

/*			n = 0;
			while (args[n] != NULL)
			{
				printf("arr: %s\n", args[n]);
				n++;
			}*/

			ft_switcher(args, my_env);
			i = 0;
			free(args);
		}
		i++;
		//printf("type=%c, item=%s\n", temp->type, temp->item);
		temp = temp->next;
	} while (temp != all.a_first);
	while (1);
	return 0;
}
