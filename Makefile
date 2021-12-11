# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 16:31:18 by ogarthar          #+#    #+#              #
#    Updated: 2021/12/11 15:53:15 by fbeatris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIST =	main.c				parser/syntax_errors.c		built_in/export_builtin.c\
		init_structs.c		parser/replace_env.c		built_in/unset_builtin.c\
		utils.c				parser/redirects.c			built_in/exit_builtin.c\
		signals.c			parser/parse_env.c			built_in/echo_builtin.c\
							parser/parser.c				built_in/pwd_builtin.c\
							parser/quotes.c				built_in/env_builtin.c\
														built_in/cd_builtin.c\


OBJ = $(LIST:.c=.o)

LIBFT_DIR =	./libft

LIBFT =	./libft/libft.a

RDLN = -lreadline -L ~/.brew/Cellar/readline/8.1.1/lib \
			  -I~/.brew/Cellar/readline/8.1.1/include

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -O3

%.o:  %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# COLORS
GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
WHITE = \033[0;37m
YELOW = \033[1;33m
B_PINK = \033[3;45m
B_GRAY = \033[1;47m
VIOLET = \033[1;35m

all : $(NAME) print

	@echo "$(GREEN)MINISHELL : ✅ D O N E ✅$(WHITE)"

$(NAME):	$(OBJ) $(LIBFT) Makefile
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RDLN) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

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

x : all
	@./minishell

print :
	@echo "	                 $(YELOW)▄▄"
	@echo "	             $(YELOW)▄▄██████          $(B_PINK)Fbeatris&$(WHITE)"
	@echo "	         $(YELOW)▄▄███████████             $(B_PINK)Ogarthar©$(WHITE)"
	@echo "	       $(YELOW)▄████████████▀██▄"
	@echo "	     $(YELOW)▄██████████▀▀$(RED)▄▄▄▄$(YELOW)▀▀█▄▄"
	@echo "	   $(YELOW)▄█████████▀▀$(GREEN)░░░$(RED)▀██▀$(GREEN)░░░$(YELOW)▀██▄"
	@echo "	  $(YELOW)▄████████▀$(GREEN)░░$(RED)▄▄▄$(GREEN)░░░░$(RED)▄▄▄$(GREEN)░░░░$(YELOW)▀██▄"
	@echo "	 $(YELOW)▄████████$(GREEN)░░$(RED)███████$(GREEN)░░$(RED)▀▀▀$(GREEN)░$(RED)▄▄█▄▄$(YELOW)▀▀█▄▄"
	@echo "	$(YELOW)▄███████▀$(GREEN)░░░$(RED)▀████▀▀$(GREEN)░░░░░░$(RED)▀███▀$(GREEN)░░░$(YELOW)▀██▄"
	@echo "	$(YELOW)████████▄▄▄▄▄▄▄▄▄$(GREEN)░░░░░░░░░░░░░$(YELOW)▄▄▄▄▄▄███▄"
	@echo "	$(YELOW)▀████████████████$(GREEN)░░░$(YELOW)▄▄$(GREEN)░░░░$(YELOW)▄$(GREEN)░░$(YELOW)███████████"
	@echo "	                $(YELOW)█$(GREEN)░░░$(YELOW)███▄███$(GREEN)░░$(YELOW)██"
	@echo "	                $(YELOW)█$(GREEN)░░░$(YELOW)██$(WHITE)    $(YELOW)█▄▄██"
	@echo "	                $(YELOW)█▄$(GREEN)░░$(YELOW)██$(WHITE)     $(YELOW)▀▀▀"
	@echo "	                 $(YELOW)▀▀▀▀ $(WHITE)"
	@echo ""

.PHONY : all clean fclean re bonus
