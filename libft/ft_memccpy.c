/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	if (dest || src)
	{
		while (n > 0)
		{
			*(unsigned char *)dest = *(unsigned char *)src;
			if (*(unsigned char *)src == (unsigned char)c)
				return (++dest);
			src++;
			dest++;
			n--;
		}
	}
	return (NULL);
}
