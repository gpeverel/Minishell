/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <gpeverel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:45:34 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_shit(const char *big, const char *little, size_t len,
size_t sizelit)
{
	size_t len2;

	len2 = 0;
	while (*little && len != 0)
	{
		if (*big == *little)
			len2++;
		else
			break ;
		big++;
		little++;
		len--;
	}
	if (len2 == sizelit)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		c_big;
	size_t	sizelit;

	if (little[0] == '\0')
		return ((char *)big);
	sizelit = ft_strlen(little);
	c_big = 0;
	while (big[c_big] != '\0' && len)
	{
		if (big[c_big] == *little)
		{
			if (find_shit(big + c_big, little, len, sizelit) == 1)
				return ((char *)big + c_big);
		}
		c_big++;
		len--;
	}
	return (NULL);
}
