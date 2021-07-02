#include "minishell.h"

char	*delete_space(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	if (str[*i] != ' ')
		return (str);
	j = *i;
	if (*i == 0)
	{
		while (str[j] == ' ')
			j++;
		tmp = ft_strdup(str + j);
	}
	else
	{
		while (str[j] == ' ')
			j++;
		tmp = ft_substr(str, 0, *i);
		tmp2 = ft_strdup(str + j - 1);
		tmp = ft_strjoin(tmp, tmp2);
		free(tmp2);
	}
	free(str);
	return(tmp);
}

char	*init_arg(char *str, int start, int end)
{
	char	*arg;
	int		i;

	i = 0;
	arg = malloc((end - start) + 1);
	while (start < end)
	{
		arg[i] = str[start];
		start++;
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char	*check_main_symbols_str(char *str, int *i, char **env)
{
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'')
		{
			str = pars_bucket(str, i);
			all.check_dol = 0;
			if (str[*i] == '<' || str[*i] == '>')
				break ;
		}
		else if (str[*i] == '\"')
		{
			str = pars_double_bucket(str, i, env);
			all.check_dol = 0;
			if (str[*i] == '<' || str[*i] == '>')
				break ;
		}
		else if (str[*i] == '<' || str[*i] == '>')
		{
			str = pars_redir_one(str, i, env);
			//break;
		}
		//if (str[*i] == '\\')
		//	str = pars_slesh(str, i);
		else if (str[*i] == '$')
		{
			str = pars_dollar(str, i, env);
			//printf("str[i] = %c\n", str[*i]);
		}
		else if (str[*i] == ' ')
			str = delete_space(str, i);
		else
			break;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*s3;
	size_t			l1;
	size_t			l2;
	size_t			i;
	size_t			j;

	i = 0;
	j = i;
	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen((char *)s1);
	l2 = ft_strlen((char *)s2);
	s3 = (unsigned char *)malloc(((l1 + l2) * sizeof(char)) + 1);
	if (!s3)
		return (0);
	while (i < l1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < l2)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free((char *)s1);
	return ((char *)s3);
}