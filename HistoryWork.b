#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "GNL/get_next_line.h"
#include "libft/libft.h"

void	get_history_from_file()
{
/* If the buffer has already been allocated, return the memory to the free pool. */
	char	*str;
	int		fd;
	int		get_check;

	fd = open("fhistory", O_RDONLY | O_CREAT, 0644);
	get_check = get_next_line(fd, &str);
	while (get_check)
	{// если файл уже создавался и там что то есть, запихиваем в историю
		add_history(str);
		get_check = get_next_line(fd, &str);
	}
	close(fd);
}

int main()
{
	char	*str;
	int		fd;

	get_history_from_file();
	fd = open("fhistory", O_WRONLY | O_APPEND, 0644);
	while (1)
	{
		str = readline ("syka_write: ");
		if (ft_strncmp("stop", str, 4) == 0)
			break;
		if (str && *str)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			add_history(str);
			printf("str = %s\n", str);
		}
	}
	close(fd);
	return 0;
}