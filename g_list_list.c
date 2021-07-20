#include "minishell.h"

void	del_elem(void)
{
	t_arg	*del_elem;

	del_elem = NULL;
	if (g_all.a_last == NULL)
		return ;
	if (g_all.a_last->next == g_all.a_last)
	{
		free(g_all.a_last);
		g_all.a_last = NULL;
	}
	else
	{
		del_elem = g_all.a_first->next;
		free(g_all.a_first);
		g_all.a_first = del_elem;
		g_all.a_last->next = del_elem;
	}
}

void	del_all_pars_list(void)
{
	t_arg	*tmp;
	t_arg	*tmpsub;

	if (g_all.a_last == NULL)
		return ;
	tmpsub = g_all.a_first;
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
	tmp->next = NULL;
	if (g_all.a_last == NULL)
	{
		g_all.a_last = tmp;
		g_all.a_first = tmp;
		g_all.a_last->next = NULL;
	}
	else
	{
		g_all.a_last->next = tmp;
		g_all.a_last = tmp;
	}
}

void	show_list(void)
{
	t_arg	*tmp;

	if (g_all.a_last == NULL)
		return ;
	tmp = g_all.a_first;
	printf("Обзор списка\n");
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
		g_all.pipe_on = 1;
		return ('p');
	}
	else
		return ('a');
}
