#include "../minishell.h"

int	ft_switcher(int fd_in, int fd_out, char **args, t_env *my_env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(my_env, args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(fd_out, &args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(fd_out);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(fd_out, my_env, &args[1]);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_print_myenv(fd_out, my_env, 0);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(my_env, &args[1]);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(&args[1]);
	else
		fr_exec(fd_in, fd_out, my_env, args);
	return (0);
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
	//dup2(*fd, 1);
	printf("fd=%d\n", (*fd));
}

void ft_reddir_l(t_arg *temp, int *fd, int *flag)
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
		(*fd) = open("<<", O_RDONLY, 0222);
	//printf("fd=%d\n", (*fd));
}

int ft_adapter(t_env *my_env)
{
	char 	**args;
	t_arg	*temp;
	int 	i;
	int 	flag;
	int 	n;
	int 	fd_in;
	int 	fd_out;
	t_arg	*arr;

	i = 0;
	fd_in = 0;
	fd_out = 1;
	flag = 0;
	temp = all.a_first;
	arr = temp;
printf(">> begin <<\n\n");

	while (temp)
	{
		//printf("type=%c, item=%s\n", temp->type, temp->item);
		if (temp->type == '1' || temp->type == '2')
		{
			//printf("1type=%c, item=%s\n", temp->type, temp->item);
			ft_reddir_r(temp, &fd_out);
			i--;
		}
		if (temp->type == '3' || temp->type == '4')
		{
			//printf("3type=%c, item=%s\n", temp->type, temp->item);
			ft_reddir_l(temp, &fd_in, &flag);
			i--;
		}
		if (temp->next == NULL && flag == 0)
		{
			//printf("2type=%c, item=%s\n", temp->type, temp->item);
			i++;
			//printf("11\n");
			//printf("type=%c, item=%s\n", temp->type, temp->item);
			//printf("i=%d\n", i);
			args = malloc(sizeof(char *) * (i + 1));
			n = 0;
			while (n < i)
			{
				if (arr->type != '1' && arr->type != '2' && arr->type != '3' && arr->type != '4')
				{
					args[n] = arr->item;
					//printf("args[n]=%s\n", args[n]);
					n++;
				}
				arr = arr->next;
			}
			args[n] = NULL;
			ft_switcher(fd_in, fd_out, args, my_env);
			if(fd_out != 1)
				close(fd_out);
			if(fd_in != 0)
				close(fd_in);
			free(args);
		}
		i++;
		//printf("i=%d\n", i);
		temp = temp->next;
	}
	//while (1);
	return 0;
}
