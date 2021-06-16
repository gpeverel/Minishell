/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:48:07 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpulst;
	t_list	*cpu;

	cpu = NULL;
	if (lst)
	{
		while (lst)
		{
			cpulst = ft_lstnew((*f)(lst->content));
			if (!cpulst)
			{
				ft_lstclear(&cpu, del);
				return (NULL);
			}
			ft_lstadd_back(&cpu, cpulst);
			lst = lst->next;
		}
	}
	return (cpu);
}
