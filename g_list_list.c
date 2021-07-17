#include "minishell.h"

void	del_elem(void)
{
	t_arg	*del_elem;

	del_elem = NULL;
	if (all.a_last == NULL)
		return ;
	if (all.a_last->next == all.a_last)
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

void	del_all_pars_list(void)
{
	t_arg	*tmp;
	t_arg	*tmpsub;

	if (all.a_last == NULL)
		return ;
	tmpsub = all.a_first;
	// tmp = tmpsub;
	// tmpsub = tmpsub->next;
	// free(tmp->item);
	// free(tmp);
	// while (tmpsub != all.a_first)
	// {
	// 	tmp = tmpsub;
	// 	tmpsub = tmpsub->next;
	// 	free(tmp->item);
	// 	free(tmp);
	// }
	while (tmpsub)
	{
		tmp = tmpsub;
		tmpsub = tmpsub->next;
		free(tmp->item);
		free(tmp);
	}
}

void	push_elem(char *str)
{
	t_arg	*tmp;

	tmp = (t_arg *)malloc(sizeof(t_arg));
	tmp->item = str;
	tmp->type = find_type_arg(str);
	tmp->next = NULL;// добавил для NULL в конце
	if (all.a_last == NULL)
	{
		//tmp->next = tmp;
		all.a_last = tmp;
		all.a_first = tmp;
		all.a_last->next = NULL;
	}
	else
	{
		//tmp->next = all.a_first;
		all.a_last->next = tmp;
		all.a_last = tmp;
		//tmp->next = NULL;// добавил для NULL в конце
	}
}

void	show_list(void)
{
	t_arg	*tmp;

	if (all.a_last == NULL)
		return ;
	tmp = all.a_first;
	printf("Обзор списка\n");
	// printf("Эл: %s type = %c\n", tmp->item, tmp->type);
	// tmp = tmp->next;
	// while (tmp != all.a_first)
	// {
	// 	printf("Эл: %s type = %c\n", tmp->item, tmp->type);
	// 	tmp = tmp->next;
	// }
	while (tmp)
	{
		printf("Эл: %s type = %c\n", tmp->item, tmp->type);
		tmp = tmp->next;
	}
}

char	find_type_arg(char *str)
{
	if (str[0] == '-')
		return ('f');
	else if (str[0] == '|' && ft_strlen(str) == 1)
	{
		all.pipe_on = 1;
		return ('p');
	}
	else
		return ('a');
}
