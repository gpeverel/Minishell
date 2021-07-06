#include "../minishell.h"

t_env	*ft_lstnew_env(char *key, char *content)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	env->key = key;
	env->content = content;
	env->next = NULL;
	return (env);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (new && lst)
	{
		if (*lst)
			ft_lstlast_env(*lst)->next = new;
		else
			*lst = new;
	}
}

void	ft_lstiter_env(t_env *lst, void (*f_key)(char *), void (*f_con)(char *))
{
	while (lst != NULL)
	{
		f_key(lst->key);
		f_con(lst->content);
		lst = lst->next;
	}
}

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


