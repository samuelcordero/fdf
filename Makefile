# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:21:07 by sacorder          #+#    #+#              #
#    Updated: 2023/06/27 00:47:22 by sacorder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/mlx.a
LIB = -L libft -lft -L minilibx-linux -lmlx -lm
NAME = fdf
FLAGS = -g -Wall -Wextra -Werror
INCLUDE = inc/fdf.h 
SRC = src/main.c src/parser.c src/transform.c #src/draw.c
SRCBONUS = src/main.c src/parser.c src/transform.c #src/draw.c
OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)
RM=/bin/rm -f

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= gcc
    LIB += -lbsd
endif

all: $(NAME)

$(LIBFT):
	@make bonus -C ./libft

$(MINILIBX):
	@make -C ./minilibx-linux
	
$(NAME): $(MINILIBX) $(LIBFT) $(OBJ) $(INCLUDE) 
	$(CC) -o $(NAME) $(OBJ) $(LIB)

bonus: $(LIBFT) $(OBJBONUS) $(INCLUDE) $(MINILIBX)
	$(CC) -o $(NAME) $(OBJBONUS) $(LIB)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	@make clean -C ./minilibx-linux
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)

fclean: clean
	@make fclean -C ./libft
	@make clean -C ./minilibx-linux
	$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus