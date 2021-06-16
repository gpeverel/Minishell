/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:06:07 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/11 19:02:37 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**free_all(char **str, int n)
{
	n--;
	while (n >= 0)
	{
		free(str[n]);
		n--;
	}
	free(str);
	return (NULL);
}

static void	find_word(char const *s, char c, int *start, int *len)
{
	*start = *start + *len;
	*len = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + *len] != c && s[*start + *len] != '\0')
		(*len)++;
}

char		**ft_split(char const *s, char c)
{
	int		start;
	int		j;
	int		end;
	char	**str;

	j = 0;
	start = 0;
	end = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = (char **)ft_calloc(sizeof(char *), (count_str(s, c) + 1))))
		return (NULL);
	while (j < count_str(s, c))
	{
		find_word(s, c, &start, &end);
		if (!(str[j] = (char *)malloc(sizeof(char) * (end + 1))))
			return (free_all(str, j));
		ft_strlcpy(str[j], &s[start], end + 1);
		j++;
	}
	return (str);
}
