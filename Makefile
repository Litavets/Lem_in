# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 19:30:41 by dstepane          #+#    #+#              #
#    Updated: 2019/03/21 19:30:42 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in
CC		= gcc
FLAGS	= -g -Wall -Wextra -Werror

SRC_DIR	= ./src/
OBJ_DIR	= ./obj/
INC_DIR	= ./inc/

LIB_DIR	= ./libft/
LIBFT 	= $(LIB_DIR)libft.a
LIB_INC	= $(LIB_DIR)includes/

SRC 	=	main.c \
			parse.c \
			validate.c \
			validate2.c \
			rooms_list.c \
			adj_list.c \
			adj_list2.c \
			bfs.c \
			bfs2.c \
			print_paths.c \
			ants_gogogo.c \
			ants_gogogo2.c \
			cleaning.c \
			debug.c 			############################

OBJ 	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lft -L $(LIB_DIR) -o $(NAME)
	@echo "\033[32m\033[100m\033[1mLem_in executable compiled.\033[0m"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(INC_DIR)lem_in.h
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIB_INC)
	@echo "	\033[96m$@\033[0m"

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@echo "\033[31mLem_in object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@@make fclean -C $(LIB_DIR)
	@echo "\033[31mLem_in executable removed.\033[0m"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
