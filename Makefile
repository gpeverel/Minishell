NAME = minishell
FLAGS = -Wall -Werror -Wextra
SRC_H = minishell.h
SRC_C = minishell.c \
		build_in/ft_cd.c \
		build_in/ft_echo.c \
		build_in/ft_env.c \
		build_in/ft_exit.c \
		build_in/ft_export.c \
		build_in/ft_list_env_work.c \
		build_in/ft_print_env.c \
		build_in/ft_pwd.c \
		build_in/ft_switcher.c \
		build_in/ft_unset.c \
		build_in/ft_fork.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		g_history_save.c \
		g_init_all.c \
		g_list_list.c \
		g_main_parser.c \
		g_pars_dollar.c \
		g_pars_dollar2.c \
		g_pars_redirect.c \
		g_pre_redirect.c \
		g_preparser.c \
		g_signals_check.c
OBJECTS = $(SRC_C:.c=.o)
LIBA = libft/libft.a
#LIBH =  -lreadline -L/Users/gpeverel/.brew/opt/readline/include ~/.brew/Cellar/readline/8.1/lib/libreadline.8.1.dylib ~/.brew/Cellar/readline/8.1/lib/libhistory.8.1.dylib -I/Users/gpeverel/.brew/opt/readline/include -ltermcap
LIBH = /Users/gpeverel/.brew/opt/readline/lib/libhistory.a /Users/gpeverel/.brew/opt/readline/lib/libreadline.a -ltermcap
all: $(LIBA) $(NAME)
$(NAME): $(LIBA) $(OBJECTS) $(SRC_H)
	gcc $(FLAGS) $(OBJECTS) $(LIBA) $(LIBH) -o $(NAME)
$(LIBA):
	make all -C libft && \
	make clean -C libft
re: fclean all
clean:
	-rm -f $(OBJECTS)
fclean: clean
	rm -rf $(NAME) test.run*
	make fclean -C libft
run: all
	./$(NAME)