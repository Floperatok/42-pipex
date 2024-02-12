# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 15:13:34 by nsalles           #+#    #+#              #
#    Updated: 2024/02/12 15:20:03 by nsalles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
NAME		=	pipex

SRC_PATH	=	src/
SRC			=	main.c \
				utils.c

OBJ_PATH	=	obj/
OBJS		=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

LIBFT		=	libft/libft.a

INCS		=	./include/

all:	$(NAME)

$(NAME):	$(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -I $(INCS) -o $@ $(OBJS) $(LIBFT)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

clean:
	rm -rf $(OBJ_PATH)
	make -C libft/ clean

fclean:
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
