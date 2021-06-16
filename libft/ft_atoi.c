/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeverel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:39:19 by gpeverel          #+#    #+#             */
/*   Updated: 2020/11/10 17:47:10 by gpeverel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int number;
	int i;
	int minus;

	i = 0;
	minus = 0;
	number = 0;
	while (str[i] == 32 || str[i] < 27)
		i++;
	if (str[i] == 45 && str[i + 1] >= 48 && str[i + 1] <= 57)
	{
		minus++;
		i++;
	}
	else if (str[i] == 43 && str[i + 1] >= 48 && str[i + 1] <= 57)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		number *= 10;
		number = number + (str[i] - 48);
		i++;
	}
	if (minus == 1)
		number *= -1;
	return (number);
}
