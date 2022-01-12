# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 16:31:18 by ogarthar          #+#    #+#              #
#    Updated: 2022/01/08 17:13:18 by ogarthar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIST =	main.c				parser/syntax_errors.c		built_in/export_builtin.c\
		init_structs.c		parser/replace_env.c		built_in/unset_builtin.c\
		child.c				parser/redirects.c			built_in/exit_builtin.c\
		utils.c				parser/parse_env.c			built_in/echo_builtin.c\
		sh_lvl.c			parser/parser.c				built_in/pwd_builtin.c\
		signals.c			parser/quotes.c				built_in/env_builtin.c\
		redirects.c			parser/redirects_utils.c	built_in/cd_builtin.c\
		pipe.c				parser/syntax_redirects.c\
		check_open.c		parser/syntax_other.c\
		pipex.c\
		heredoc.c\
		free_all.c\
		sort_env.c


OBJ = $(LIST:.c=.o)

LIBFT_DIR =	./libft

LIBFT =	./libft/libft.a

RDLN = -lreadline -L ~/.brew/Cellar/readline/8.1.1/lib \
			  -I~/.brew/Cellar/readline/8.1.1/include

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -O3

%.o:  %.c Makefile minishell.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# COLORS
GREEN = \033[1;32m
BLUE = \033[1;36m
RED = \033[1;31m
WHITE = \033[0;37m
YELOW = \033[1;33m
B_PINK = \033[3;45m
B_GRAY = \033[1;47m
VIOLET = \033[1;35m

all : $(NAME) print

	@echo "$(GREEN)MINISHELL : ✅ D O N E ✅$(WHITE)"

$(NAME):	$(OBJ) $(LIBFT) Makefile minishell.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RDLN) -o $(NAME) -lreadline -L \
	~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

.FORCE :
$(LIBFT): .FORCE
	make -C $(LIBFT_DIR)
	@echo "$(GREEN)LIBFT : ✅ D O N E ✅$(WHITE)"

re : fclean all

# bonus : all

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)LIBFT : 💣 D E L E T E D 💣$(WHITE)"
	rm -f $(NAME)
	@echo "$(RED)MINISHELL : 💣 D E L E T E D 💣$(WHITE)"

x : all;	@./minishell

print :
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣤⠤⠴⠶⠶⠶⠶⠤⢤⣄⣀⣠⣤⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⠤⠒⣚⠉⠉⠉⠉⠉⠉⠀⠀⠀$(BLUE)⢠⡄⠀⢀⣭⣭⡍⠀⠀⣀⠀⠀⢀⠀$(YELOW)⠀⠉⠉⠩⠍⠙⠒⠦⠤⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠴⠒⢋⠉⠀⠀⠀⠀$(BLUE)⢀⣀⠀⠀⣶⡄⡀⣾⡆⠀⢸⡇⠀⠸⣷⣤⡀⠀⠀⣿⡇⠀⣿⡇⠀⣰⣶⣶⣶⠀⠀⠀$(YELOW)⠐⠐⠀⠉⠛⠛⠶⢤⣀⡀⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀$(BLUE)⣿⡆⢰⣿⠀⠀⢸⣿⠀⠀⣿⡻⣦⣿⡇⠀⢸⡇⠀⢀⣀⣹⣿⠀⠀⣿⡟⠛⣿⡇⠀⣿⣧⣤⡄⠀⢸⡇$(YELOW)⠐⠀$(BLUE)⠀⣤⡄⠀⠀⠀$(YELOW)⢂⡌⡇"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀$(BLUE)⢸⡿⣿⣿⢿⡆⠀⢸⣿⠀⠀⣿⠀⠙⣿⡇⠀⠘⣃⣀⣈⣛⠛⠁⡀⡰⠿⠇⠀⠿⠇⠀⣿⣧⣤⣤⠀⢼⡇⠀⠀⠀⣿⡇⠀⠀⠀$(YELOW)⠈⡰⠃"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣆⠀$(BLUE)⠾⠃⠹⠏⠸⠷⢀⣘⠛⣀$(YELOW)⠀⣬⣄⣠⣾⡷⠾⠽⠯⠭⠽⠶⠶⠦⠤⠤⠤⠭⣯⣙⣒⣒⠿⢿⣿⣛⠀$(BLUE)⠾⠷⠶⠶⠀⣿⣇⣀⣀⠀$(YELOW)⣰⠁"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣄⠀⣀⣤⣴⡿⣤⠿⠟⠛⠛$(RED)⣠⣭⣿⣿⣿⣿⣿⣶⡄$(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠛⠋⠰⠿⢠⣼⣷⣶⣦$(BLUE)⠉⣉⠉⠉$(YELOW)⣰⠃⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⠽⠋⠁⠀⠀⠀⠀$(RED)⣠⣾⣿⣿⡿⣿⣿⣿⣿⣿⣿⣦$(YELOW)⠀⠀⠀⠀⠀⢦⣀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠓⠻⠧⣰⠏⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣆⠀⠀⠀⠀⠀$(RED)⢰⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣧$(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⢀⡿⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡆⠀⠀⠀⠀$(RED)⢸⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⢀⣤⣶⣶⣶⣶⣶⣦⣄$(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⣼⠁⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠀⠀⠀⠀$(RED)⠸⣿⣶⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣶⣿⣿⣿⣷⡄$(YELOW)⠀⠀⠀⠀⠀⣰⠃⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡆⠸⡀⢀⠀$(RED)⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⣼⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⡆$(YELOW)⠀⠀⠀⢰⠃⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡀⠉⠁⠀⠀$(RED)⠈⠻⢿⣽⣟⣛⣿⣿⣿⠿⠃⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿$(YELOW)⠀⠀⠀⡎⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡀⠀⠀⠀⠀⠀⠀⠀$(RED)⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣶⣿⣿⣿⣟⣿⣿⣿⣿⣿⡿$(YELOW)⠀⠂⡸⠀⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⡀⠀⠐⠐⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⢻⣿⣿⣿⣿⣹⣿⣿⣿⣿⣿⣿⡿⠁$(YELOW)⠈⢠⠃⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱$(RED)⣀⣤⣴⣶⣶⣤⣦⣄⡀⠀⠀$(YELOW)⠈⢧⣀⡰⠀⠀⠀⠀$(RED)⠻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁$(YELOW)⠀⢠⠋⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⢿⣿⣿⣿⣯⣟⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠉⠙⠛⠛⠛⠉⠁$(YELOW)⠀⠀⠀⢠⠃⠀"
	@echo " $(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆$(YELOW)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⣠⣤⣤⣤⢀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⣤⠄⠀⠀$(RED)⠈⢿⣿⣶⣿⣶⣿⣿⣿⣿⣯$(YELOW)⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⠀⠀⠀⠀⠀⡇⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⢀⣿⣥⣤⠀⢸⡷⠶⣶⠀⣴⡖⢲⣦⠀⠲⢒⣶⡄⢰⣿⠷⠂⣶⠦⠶⢰⡖⢀⣶⠒⠶$(RED)⠈⢿⣿⣿⣿⣟⣿⣿⣿⣿$(YELOW)⠀⠀⠈⠉⠀⠀⠀$(RED)⢀⣠⣴⣶⣶⣦⣤⣤⣀⢀$(YELOW)⠀⠀⡇⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⣸⡟⠀⠀⠀⣿⣀⣰⡿⠐⣿⣉⣉⡉⣴⣏⣉⣿⠀⢸⣟⣀⢸⡟⠀⠀⣿⠇⣀⣉⣻⡷⠀$(RED)⠈⣿⣿⣿⣿⣿⣿⣹⠏⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣻⣿⣿⣿⡿$(YELOW)⠦⠴⠃⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠉⠁⠀⠀⠈⠉⠉⠉⠀⠀⠈⠉⠉⠀⠈⠉⠉⠁⠀⠈⠉⠁⠈⠁⠀⠀⠉⠀⠉⠉⠉⠀⠀⠀$(RED)⠹⣿⣹⣿⣿⡷⠃⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣶⣿⣿⣿⣿⣿⡿⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀$(RED)⠹⡿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣹⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢾⣏⣹⠗⠀⠀⠀⠀⠀$(YELOW)⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⢸⣿⣿⣿⣿⣶⣿⣿⠏⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠙⢷⣾⠃⠀⠀⠀⠀⠀$(YELOW)⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠘⣿⣶⣿⣟⣿⣿⠇⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠛⠋⠛⠃⠀⠀⠀⠀⠀$(YELOW)⠈⡇⠀⠀⠂⠀⡀⠀⠀⠀⠀$(RED)⠘⢿⣿⣿⣿⡟⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⡇⠀⠀⢦⣀⠇⠀⠀⠀⠀⠀⠀$(RED)⠙⣿⡟⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⢠⣴⠶⢶⣦⠀⠀⢀⡀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⢀⣶⡀⠀⣾⡇⣀⠀⠀⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⣷⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⢰⠏⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⣿⠁⠀⢀⣿⢀⣾⠋⢙⡿⠀⣨⡭⣽⡗⢀⣿⠛⠋⢹⡟⠉⢰⣿⠉⣿⡇⢀⣭⣭⣿⠇⢰⡟⠛⠃⠀⠀⠀$(YELOW)⠻⣄⡼⢧⠀⠀⠀⠀⠀⠀⠀⢠⡟⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠻⠶⠶⠿⠋⠘⠿⠶⣾⠇⠸⠿⠤⠿⠃⠸⠟⠀⠀⠿⠧⠄⠾⠇⠀⠿⠀⠿⠧⠼⠿⠀⠾⠁⠀⠀⠀⠀⠀⠀⠀$(YELOW)⠈⣇⠀⠀⡇⢀⠀⠀⣾⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠘⠓⠚⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⢸⡄⠀⠙⠋⠀⢠⡏⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠤⠤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⠸⡇⠄⠀⣾⠛⠋⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⢡⡖⠒⠈⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⡇⠀⠀⣿⠀⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⡘⠳⠴⢀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⢷⠀⠀⣿⠀⠀"
	@echo " $(VIOLET)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠓⠚⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(YELOW)⠘⢦⡴⠇⠀⠀"
	@echo ""⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

.PHONY : all clean fclean re bonus
