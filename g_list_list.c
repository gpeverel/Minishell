#include "minishell.h"

void	del_elem()
{
	t_arg	*del_elem = NULL;
	if (all.a_last == NULL)
		return ;
	if (all.a_last->next == all.a_last) // Если в кольце последний элемент
	{
		free(all.a_last);
		all.a_last = NULL;
	}
	else
	{
		del_elem = all.a_first->next;
		free(all.a_first);
		all.a_first = del_elem;
		all.a_last->next = del_elem;
	}
}

/*int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (!(str1[i] || str2[i]))
		return (str1[i] - str2[i]);
	return (0);
}*/

void	push_elem(char *str)
{
	t_arg*	tmp;

	tmp = (t_arg*)malloc(sizeof(t_arg));
	tmp->item = str;
	tmp->type = find_type_arg(str);
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

void	show_list()
{
	t_arg* tmp;
	t_arg* tmpsub;

	if (all.a_last == NULL)
		return;
	tmp = all.a_first;
	printf("Обзор списка\n");
	do
	{
		printf("Эл: %s type = %c\n", tmp->item, tmp->type);
		tmp = tmp->next;
	} while (tmp != all.a_first);
}

char	find_type_arg(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return ('c');
	else if (!ft_strcmp(str, "cd"))
		return ('c');
	else if (!ft_strcmp(str, "pwd"))
		return ('c');
	else if (!ft_strcmp(str, "export"))
		return ('c');
	else if (!ft_strcmp(str, "unset"))
		return ('c');
	else if (!ft_strcmp(str, "env"))
		return ('c');
	else if (!ft_strcmp(str, "exit"))
		return ('c');
	else if (str[0] == '-')
		return ('f');
	else
		return ('a');
}