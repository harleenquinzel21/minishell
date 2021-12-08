# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 16:31:18 by ogarthar          #+#    #+#              #
#    Updated: 2021/12/09 00:00:51 by fbeatris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIST =	main.c\
		init_structs.c\
		built_in/exit_builtin.c\
		built_in/echo_builtin.c\
		built_in/pwd_builtin.c\
		built_in/env_builtin.c\
		built_in/cd_builtin.c\
		parser/parser.c \
		parser/quotes.c \
		parser/replace_env.c \
		parser/syntax_errors.c \
		parser/redirects.c \
		parser/parse_env.c

# built_in/export_builtin.c\

OBJ = $(LIST:.c=.o)

LIBFT_DIR =	./libft

LIBFT =	./libft/libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -O3

%.o:  %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# COLORS
GREEN = \033[1;32m
RED = \033[1;31m
WHITE = \033[0;37m

all : $(NAME)

	@echo "$(GREEN)MINISHELL : ✅ D O N E ✅$(WHITE)"

$(NAME):	$(OBJ) $(LIBFT) Makefile
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

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

.PHONY : all clean fclean re bonus
