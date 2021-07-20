#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <term.h>
# include <dirent.h>
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>

typedef struct s_arg
{
	char			type;
	char			*item;
	struct s_arg	*next;
}				t_arg;

typedef struct s_all
{
	char	argument;
	t_arg	*a_first;
	t_arg	*a_last;
	int		check_dol;
	int		pipe_on;
	int		error;
	int		flag;
	int		notfile;
	int		flag_red;

}				t_all;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

t_all			g_all;

char	*prepars_pipe_errors(char *str, int *i);
char	*ft_error(char *err);
char	*pars_bucket(char *str, int *i);
char	*pars_double_bucket(char *str, int *i, t_env *my_env);
char	*command_parser(char *str, t_env *my_env);
char	*pars_dollar(char *str, int *i, t_env *my_env);
char	*get_key_in_env(t_env *my_env, char *key);
char	*find_key_env(t_env *my_env, char *key, int *k, int *z);
int		ifkey(char c);
void	while_key_end(int *i, char *str);
void	if_str_null(char **tmp2, char *str, int *i);
char	*join_all_part(char **key, char *tmp2, char *str);
int		check_pipe_in_str(char *str, int *i);
char	*pars_redir_one(char *str, int *i, t_env *my_env);
int		check_main_symb(char **str, int *j, t_env *my_env);
void	redir_go_check_line(char **str, int *j, t_env *my_env);
void	push_redir(char *str, int i, char *filename);
char	*ft_strnewcpy(char *str, int size);
void	work_left_two_redir(t_env *my_env);
void	left_two_redir_str_push(char *str, int fd, t_env *my_env);
char	*delete_space(char *str, int *i);
char	*init_arg(char *str, int start, int end);
char	*check_main_symbols_str(char *str, int *i, t_env *my_env);
int		check_bucket_in_str(char **str, int *i, t_env *my_env);
void	initstruct(void);
char	*join_str_bucket(char *str, int *i, int j);
void	del_elem(void);
void	push_elem(char *str);
void	show_list(void);
char	find_type_arg(char *str);
void	del_all_pars_list(void);
char	*redir_pre_pars(char *str);
int		backet_check(char *str, int buck, int *place, char c);
char	*recalcul_backet(char *str);
char	*pipe_pre_pars(char *str, int *i);
char	*prepars_backet_check(char *str, int *i);
int		skip_first_redir(char *str, int i, char fir, char sec);
char	*skip_clear_filename(char *str, int *i);
char	*redir_pre_side(char *str, int *i);
int		command_pre_parser(char *str);
void	get_history_from_file(void);
char	*ft_substr_g(char const *s, unsigned int start, int len);
void	rl_replace_line(const char *c, int i);
void	quit_signals(void);
void	handle_signals(void);
int		main_loop_line(int fd, t_env *my_env);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(int fd, char **str);
int		ft_cd(t_env *my_env, char *path);
int		ft_pwd(int fd);
int		ft_export(int fd, t_env *my_env, char **args);
t_env	*ft_create_my_env(char **env, t_env *my_env);
t_env	*ft_lstnew_env(char *key, char *content);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	f(t_env *l, void (*k)(char *, int), void (*c)(char *, int), int fd);
void	ft_print_myenv(int fd, t_env *my_env, int i);
void	ft_lstclear_env(t_env **lst);
char	**ft_find_env(t_env *my_env, char *key);
char	*ft_get_content(char *source);
char	*ft_get_key(char *str);
t_env	*ft_unset(t_env *my_env, char **args);
void	ft_exit(char **args);
int		ft_adapter(t_env *my_env);
int		ft_lstsize_env(t_env *lst);
void	fr_exec(int *fd, t_env *my_env, char **args, pid_t pid);
char	*ft_path_command(char *path, char *command);
char	*ft_strcat(char *dst, char *src, char *three);
void	ft_free_arr(char **env);
char	*ft_get_path(t_env *my_env, char *arg);
char	**ft_create_env_arr(t_env *my_env);
t_env	*ft_find_node(t_env *my_env, char *key);
int		getExec(t_env *my_env, int i, int *fd, t_arg *arr);
char	**ft_args(int i, t_arg *arr);
void	ft_reddir_l(t_arg *temp, int *fd, int *flag);
void	ft_reddir_r(t_arg *temp, int *fd);

#endif