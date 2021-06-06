# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 14:33:51 by hchorfi           #+#    #+#              #
#    Updated: 2021/05/21 20:49:51 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = ./libft

SRCS = main.c\
		export.c\
		export_utils.c\
		export_utils2.c\
		env.c\
		unset.c\
		pwd.c\
		cd.c\
		bin.c\
		bin_utils.c\
		parse/split.c\
		parse/split_utils1.c\
		parse/split_utils2.c\
		parse/split_utils3.c\
		parse/split_utils4.c\
		parse/split_utils5.c\
		parse/split_utils6.c\
		echo.c\
		exit.c\
		term.c\
		term_keys.c\
		term_utils.c\
		utils1.c\
		utils2.c\
		utils3.c\
		redirections.c\
		redirections_utils.c\
		builtin_utils.c\
		tockens.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g #-fsanitize=address
$(NAME) :
	make -C $(LIBFT_PATH)
	gcc -g $(ASAN) $(SRCS) libft/libft.a -lncurses -o $(NAME)
	
all: $(NAME)

rebuild:
	make re -C libft ; make re -C ft_printf ; make re

clean:
	make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all
