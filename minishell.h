#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>

// minishell.c
char	*ft_error(char *err);
char	*pars_bucket(char *str, int *i);
char	*pars_double_bucket(char *str, int *i);
char	*pars_slesh(char *str, int *i);

//pars_dollar
char	*pars_dollar(char *str, int *i, char **env);
char	*get_key_in_env(char **env, char *key);
char	*find_key_env(char **env, char *key, int *k, int *z);
int		ifkey(char c);

//build-in
typedef struct		s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}					t_env;

int		ft_strcmp(char *s1, char *s2);
int		ft_echo(int fd, char **str);
int		ft_cd(char *path, char *home);
int		ft_pwd(int fd);
int		ft_export(char **args, char **env);

#endif
