# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchorfi <hchorfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 23:08:49 by hchorfi           #+#    #+#              #
#    Updated: 2020/10/17 13:46:12 by hchorfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

TEST = hakuna_matata

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c\
	  ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strchr.c ft_strrchr.c\
	  ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c\
	  ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c\
	  ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c ft_substr.c\
	  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	  ft_putendl_fd.c ft_putnbr_fd.c ft_memmove.c ft_strlcat.c\
	  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	  ft_lstadd_back.c\

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

OBG = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memchr.o\
	  ft_memcmp.o ft_strlen.o ft_strlcpy.o ft_strchr.o ft_strrchr.o\
	  ft_strnstr.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o\
	  ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o\
	  ft_calloc.o ft_strdup.o ft_putchar_fd.o ft_putstr_fd.o ft_substr.o\
	  ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o\
	  ft_putendl_fd.o ft_putnbr_fd.o ft_memmove.o ft_strlcat.o\
	  ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o\
	  ft_lstadd_back.o\

BOBG = ft_lstnew_bonus.o ft_lstadd_front_bonus.o ft_lstsize_bonus.o

$(NAME) :
	gcc $(FLAGS) -c $(SRC)
	ar rc $(NAME) $(OBG)
	ranlib $(NAME)

test:
	gcc $(FLAGS) -o $(TEST) $(TEST).c -L. -lft

norme:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(BSRC)

bonus:
	gcc $(FLAGS) -c $(BSRC)
	ar rs $(NAME) $(BOBG)

clean:
	/bin/rm -f $(OBG) $(BOBG)

fclean:
	/bin/rm -f $(NAME) $(OBG) $(BOBG)

re: fclean all

