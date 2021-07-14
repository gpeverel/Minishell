#include "minishell.h"

void	get_history_from_file()
{
	char	*str;
	int		fd;
	int		get_check;

	fd = open("fhistory", O_RDONLY | O_CREAT, 0644);
	get_check = get_next_line(fd, &str);
	while (get_check)
	{// если файл уже создавался и там что то есть, запихиваем в историю
		add_history(str);
		free(str);
		get_check = get_next_line(fd, &str);
	}
	free(str);
	close(fd);
}