#include "../minishell.h"

t_env	*ft_lstnew_env(char *key, char *content)
{
	t_env	*str;

	if (!(str = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	str->key = key;
	str->content = content;
	str->next = NULL;
	return (str);
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

void	ft_lstiter_env(t_env *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}


