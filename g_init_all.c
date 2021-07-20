#include "minishell.h"

void	initstruct(void)
{
	g_all.a_first = NULL;
	g_all.a_last = NULL;
	g_all.check_dol = 0;
	g_all.pipe_on = 0;
	g_all.flag = 0;
}

char	*join_str_bucket(char *str, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + (*i)-- + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	free(str);
	return (tmp);
}
