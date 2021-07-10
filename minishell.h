#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"
#include "GNL/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>

// typedef struct	s_redir
// {
// 	char	type;
// 	char	*file_name;
// 	struct s_redir	*next;
// }				t_red;

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
	int		pipe_on;

}				t_all;

typedef struct    s_env
{
   char         *key;
   char         *content;
   struct s_env   *next;
   struct s_env   *prev;
}              t_env;

t_all all;// единственная глобальная переменная



// minishell.c
char	*ft_error(char *err);
char	*pars_bucket(char *str, int *i);
char	*pars_double_bucket(char *str, int *i, t_env *my_env);
char	*command_parser(char *str, t_env *my_env);
//char	*pars_slesh(char *str, int *i);

//pars_dollar
char	*pars_dollar(char *str, int *i, t_env *my_env);
char	*get_key_in_env(t_env *my_env, char *key);
char	*find_key_env(t_env *my_env, char *key, int *k, int *z);
int		ifkey(char c);

//		dollar2
void	while_key_end(int *i, char *str);
void	if_str_null(char **tmp2, char *str, int *i);
char	*join_all_part(char **key, char *tmp2, char *str);
int		check_pipe_in_str(char *str, int *i);

// pars_redirect
char	*pars_redir_one(char *str, int *i, t_env *my_env);
int		check_main_symb(char **str, int *j, t_env *my_env);
void	redir_go_check_line(char **str, int *j, t_env *my_env);
void	push_redir(char *str, int i, char *filename);
char	*ft_strnewcpy(char *str, int size);

//main_parser
char	*delete_space(char *str, int *i);
char	*init_arg(char *str, int start, int end);
//void	check_main_symbols_str(char **str, int *i, char **env);
char	*check_main_symbols_str(char *str, int *i, t_env *my_env);
int		check_bucket_in_str(char **str, int *i, t_env *my_env);

//init_all
void	initstruct();

//list_list
void	del_elem();
//int		ft_strcmp(char *str1, char *str2);
void	push_elem(char *str);
void	show_list();
char	find_type_arg(char *str);
void	del_all_pars_list();

//	preparser
char	*redir_pre_pars(char *str);
int		backet_check(char *str, int buck, int *place, char c);
char	*recalcul_backet(char *str);

//	pre_redirect
int		skip_first_redir(char *str, int i, char fir, char sec);
char	*skip_clear_filename(char *str, int *i);
//char	*redir_pre_right(char *str, int *i); // убрать эти функции из файла
//char	*redir_pre_left(char *str, int *i);
char	*redir_pre_side(char *str, int *i);
int		command_pre_parser(char *str);

//		history
void	get_history_from_file();


int       ft_strcmp(char *s1, char *s2);
int       ft_echo(int fd, char **str);
int       ft_cd(t_env *my_env, char *path);
int       ft_pwd(int fd);
int       ft_export(t_env *my_env, char **args);
t_env  *ft_create_my_env(char **env, t_env *my_env);
t_env  *ft_lstnew_env(char *key, char *content);
t_env  *ft_lstlast_env(t_env *lst);
void   ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstiter_env(t_env *lst, void (*f_key)(char *), void (*f_con)(char *));
void   ft_print_myenv(t_env *my_env, int i);
void   ft_lstclear_env(t_env **lst);
char   **ft_find_env(t_env *my_env, char *key);
char   *ft_get_content(char *source);
char   *ft_get_key(char *str);
t_env  *ft_unset(t_env *my_env, char **args);
void   ft_exit(char **args);

#endif