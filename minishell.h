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
	struct s_env	*prev;
}					t_env;

int		ft_strcmp(char *s1, char *s2);
int		ft_echo(int fd, char **str);
int		ft_cd(t_env	*my_env, char *path);
int		ft_pwd(int fd);
int		ft_export(t_env *my_env, char **args);
t_env 	*ft_create_my_env(char **env, t_env *my_env);
t_env	*ft_lstnew_env(char *key, char *content);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstiter_env(t_env *lst, void (*f_key)(char *), void (*f_con)(char *));
void 	ft_print_myenv(t_env *my_env, int i);
void	ft_lstclear_env(t_env **lst);
char	**ft_find_env(t_env *my_env, char *key);
char	*ft_get_content(char *source);
char	*ft_get_key(char *str);
t_env	*ft_unset(t_env *my_env, char **args);

#endif
