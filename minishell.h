#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "libft/libft.h"

# define echo 0b00000001;
# define cd 0b00000001;
# define pwd 0b00000001;
# define export 0b00000001;
# define unset 0b00000001;
# define enva 0b00000001;
# define exit 0b00000001;

typedef struct	s_redir
{
	int		red_count;
	int		num;
	char	type;

}				t_red;

typedef struct	s_all
{
	char	argument;// хранится бинарный код команды
	int		red_count;
	t_red	*red_work;

}				t_all;

t_all all;



// minishell.c
char	*ft_error(char *err);
char	*pars_bucket(char *str, int *i);
char	*pars_double_bucket(char *str, int *i, char **env);
char	*pars_slesh(char *str, int *i);

//pars_dollar
char	*pars_dollar(char *str, int *i, char **env);
char	*get_key_in_env(char **env, char *key);
char	*find_key_env(char **env, char *key, int *k, int *z);
int		ifkey(char c);

#endif