/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:19:26 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_shit1end(char const *s1, char const *set)
{
	int		len;
	size_t	i;

	len = (int)ft_strlen(s1) - 1;
	while (len != 0)
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[len] == set[i])
				break ;
			i++;
		}
		if (i == ft_strlen(set))
			break ;
		len--;
	}
	return (len);
}

static int	find_shit1begin(char const *s1, char const *set)
{
	size_t	i;
	int		j;

	j = 0;
	while (s1[j] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[j] == set[i])
				break ;
			i++;
		}
		if (i == ft_strlen(set))
			break ;
		j++;
	}
	return (j);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		begin;
	int		end;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	begin = find_shit1begin(s1, set);
	end = find_shit1end(s1, set);
	if (end == 0)
		end = ft_strlen(s1);
	s = malloc(sizeof(char) * (end - begin + 1) + 1);
	if (!s)
		return (NULL);
	while (begin != end + 1)
	{
		s[i] = s1[begin];
		begin++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
