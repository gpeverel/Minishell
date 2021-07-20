#include "../minishell.h"

void	ft_lstclear_env(t_env **lst)
{
	t_env	*l;

	if (*lst)
	{
		while (*lst)
		{
			l = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			(*lst) = NULL;
			*lst = l;
		}
	}
}
