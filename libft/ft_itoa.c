#include "libft.h"

static char	*ft_strndup(char *str, size_t len)
{
	char	*dst;
	char	*strcp;

	dst = (char *)malloc(len + 1);
	if (NULL == dst)
		return (NULL);
	strcp = dst;
	while (len-- != 0)
		*strcp++ = *str++;
	*strcp = '\0';
	return (dst);
}

char	*ft_itoa(long long int n)
{
	char					*res;
	char					buf[25];
	unsigned long long int	nbr;
	size_t					len;

	len = 22;
	buf[len--] = '\0';
	nbr = (unsigned long long int)n;
	if (n < 0)
		nbr = (unsigned long long int)(-n);
	else if (n == 0)
		buf[len--] = '0';
	while (nbr != 0)
	{
		buf[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		buf[len--] = '-';
	res = ft_strndup(&buf[len + 1], 21 - len);
	if (res == NULL)
		return (NULL);
	return (res);
}
