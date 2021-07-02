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
	char	type;
	char	*file_name;
	struct s_redir	*next;
}				t_red;

typedef struct	s_arg
{
	char			type;
	char			*item;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_all
{
	char	argument;// хранится бинарный код команды
	//int		red_count;
	//t_red	*red_work;
	//char	**arg;
	t_arg	*a_first;
	t_arg	*a_last;
	int		check_dol;


}				t_all;

t_all all;// единственная глобальная переменная



// minishell.c
char	*ft_error(char *err);
char	*pars_bucket(char *str, int *i);
char	*pars_double_bucket(char *str, int *i, char **env);
//char	*pars_slesh(char *str, int *i);

//pars_dollar
char	*pars_dollar(char *str, int *i, char **env);
char	*get_key_in_env(char **env, char *key);
char	*find_key_env(char **env, char *key, int *k, int *z);
int		ifkey(char c);

// pars_redirect
char	*pars_redir_one(char *str, int *i, char **env);
int		delete_redir();
void	push_redir(char *str, int i, char *filename);
char	*ft_strnewcpy(char *str, int size);

//main_parser
char	*delete_space(char *str, int *i);
char	*init_arg(char *str, int start, int end);
//void	check_main_symbols_str(char **str, int *i, char **env);
char	*check_main_symbols_str(char *str, int *i, char **env);

//init_all
void	initstruct();

//list_list
void	del_elem();
int		ft_strcmp(char *str1, char *str2);
void	push_elem(char *str);
void	show_list();
char	find_type_arg(char *str);

#endif