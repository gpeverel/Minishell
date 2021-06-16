/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <gpeverel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:35:12 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	n = 0;
	i = 0;
	while (dst[i] != '\0')
		i++;
	while ((n < size - len - 1) && src[n] != '\0')
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (len + ft_strlen(src));
}
