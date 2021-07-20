#include "minishell.h"

void	get_history_from_file(void)
{
	char	*str;
	int		fd;
	int		get_check;

	fd = open("fhistory", O_RDONLY | O_CREAT, 0644);
	get_check = get_next_line(fd, &str);
	while (get_check)
	{
		add_history(str);
		free(str);
		get_check = get_next_line(fd, &str);
	}
	free(str);
	close(fd);
}

char	*ft_substr_g(char const *s, unsigned int start, int len)
{
	char			*cpy;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len <= 0)
	{
		cpy = malloc(sizeof(char));
		cpy[i] = '\0';
		return (cpy);
	}
	cpy = malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	while (len != 0 && s[start] != '\0')
	{
		cpy[i] = s[start];
		start++;
		len--;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
