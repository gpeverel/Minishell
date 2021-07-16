#include "minishell.h"

void	initstruct(void)
{
	all.a_first = NULL;
	all.a_last = NULL;
	all.check_dol = 0;
	all.pipe_on = 0;
	all.flag = 0;
	//all.error = 0;
}

char	*join_str_bucket(char *str, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + (*i)-- + 1);// уменьшаю I на 1 чтобы не переходить
	tmp = ft_strjoin(tmp, tmp2);//			к следующему символу
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	free(str);
	return (tmp);
}
