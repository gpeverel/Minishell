#include "minishell.h"

char	*ft_strnewcpy(char *str, int size)
{
	char	*tmp;
	int		len;

	if (str != NULL)
	{
		len = ft_strlen(str);
		if (len < size)
			size = len;
		tmp = malloc(sizeof(char) * size + 1);
		tmp[size] = '\0';
		while (--size != -1)
		{
			tmp[size] = str[size];
		}
		return (tmp);
	}
	return (NULL);
}

void	push_redir(char *str, int i, char *filename)
{
	t_arg	*tmp;

	tmp = malloc(sizeof(t_arg));
	if (str[i] == '>' && str[i + 1] != '>')
		tmp->type = '1';
	else if (str[i] == '>' && str[i + 1] == '>')
		tmp->type = '2';
	else if (str[i] == '<' && str[i + 1] != '<')
		tmp->type = '3';
		else if (str[i] == '<' && str[i + 1] == '<')
		tmp->type = '4';
	tmp->item = filename;
	printf("\nfile name = %s, type = %c\n", tmp->item, tmp->type);
	//tmp->next = all.red_work;
	//all.red_work = tmp;
	if (all.a_last == NULL)
	{
		tmp->next = tmp;
		all.a_last = tmp;
		all.a_first = tmp;
	}
	else
	{
		tmp->next = all.a_first;
		all.a_last->next = tmp;
		all.a_last = tmp;
	}
}

// int		delete_redir()
// {
// 	t_red	*out;

// 	if (all.red_work != NULL)
// 	{
// 		out = all.red_work;
// 		all.red_work = all.red_work->next;
// 		free(out->file_name);
// 		free(out);
// 		return (1);
// 	}
// 	return (0);
// }

char	*pars_redir_one(char *str, int *i, char **env)
{
	int j;
	int	z;
	char	*tmp;

	j = *i + 1;
	if (str[*i + 1] == '>')
		j++;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	//printf("%d\n", j);
	z = j--;
	while (str[++j])
	{
		printf("%c", str[j]);
		if (str[j] == '\'')
			str = pars_bucket(str, &j);
		if (str[j] == '\"')
			str = pars_double_bucket(str, &j, env);
		//if (str[j] == '\\')
		//	str = pars_slesh(str, &j);
		if (str[j] == '$')
			str = pars_dollar(str, &j, env);
		if (str[j] == '>' || str[j] == '<')
		{
			printf("%d\n", j);
			ft_error("Redirect error\n");
		}
		if (str[j] == ' ' || str[j] == '\t'|| str[j] == '\0')
			break;
	}
	push_redir(str, *i, ft_strnewcpy(str + z, j - z));// пихаем в структуру
	tmp = ft_substr(str, 0, *i - 1);
	tmp = ft_strjoin(tmp, str + j);
	//while (tmp[*i] == ' ')
	//	(*i)++;
	//tmp = delete_space(tmp, i);
	//free(str);
	all.check_dol = 1;
	//*i = j;
	return (tmp);

}