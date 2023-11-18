####################################################################
#                            CONFIG                                #
####################################################################

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g
NAME		=	pipex

####################################################################
#                            FILES                                 #
####################################################################

SRC			=	main.c utils.c

LIBFT		=	libft/libft.a

OBJ			=	$(SRC:.c=.o)

####################################################################
#                            PATHS                                 #
####################################################################

OBJ_PATH	=	obj/
SRC_PATH	=	src/

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

INCS		=	./include/


####################################################################
#                            RULES                                 #
####################################################################

all:	$(NAME)

$(NAME):	$(OBJS)
	@echo -n "$(COM_COLOR)compiling libft... $(NO_COLOR)"
	@make -s --no-print-directory -C libft/
	@echo "$(COM_COLOR)done: $(OK_COLOR)[✓]$(NO_COLOR)"
	@echo -n "$(COM_COLOR)compiling $(NAME)... $(NO_COLOR)"
	@$(CC) $(CFLAGS) -I $(INCS) -o $@ $(OBJS) $(LIBFT)
	@echo "$(COM_COLOR)done: $(OK_COLOR)[✓]$(NO_COLOR)"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(COM_COLOR)clean:                   $(OK_COLOR)[✓]$(NO_COLOR)"
	@make --no-print-directory -C libft/ clean

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@echo "$(COM_COLOR)fclean:                  $(OK_COLOR)[✓]$(NO_COLOR)"
	@make --no-print-directory -C libft/ fclean

re: fclean all

####################################################################
#                            COLORS                                #
####################################################################

COM_COLOR   = \033[0;34m
OK_COLOR    = \033[0;32m
NO_COLOR    = \033[m