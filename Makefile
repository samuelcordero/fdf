# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 15:21:07 by sacorder          #+#    #+#              #
#    Updated: 2023/08/30 01:04:21 by sacorder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
LD = -L libft -lft -lm
NAME = fdf
FLAGS = -Wall -Wextra -Werror -O3 #-g3 -fsanitize=address
INCLUDE = inc/fdf.h 
SRC = src/main.c src/parser.c src/draw.c src/transform.c src/utils.c src/hooks.c src/wu_line.c src/math_utils.c src/draw_utils.c src/point.c src/help.c
OBJ = $(SRC:.c=.o)
RM=/bin/rm -f
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
	# mac
    CC = gcc
    FLAGS += -D MAC_OS -Iminilibx_macos
    LD += -framework OpenGL -framework AppKit -L minilibx_macos -lmlx 
    MINILIBX = minilibx_macos/libmlx.a
    MINILIB_PATH = ./minilibx_macos
else
	#Linux and others...
    CC	= gcc
    LD += -lbsd -L minilibx-linux -lmlx -lXext -lX11
    MINILIBX = minilibx-linux/libmlx.a
    MINILIB_PATH = ./minilibx-linux
endif

all: $(NAME)

$(LIBFT):
	@make bonus -C ./libft

$(MINILIBX):
	@make -C $(MINILIB_PATH)
	
$(NAME): $(LIBFT) $(MINILIBX) $(OBJ) $(INCLUDE) 
	$(CC) $(FLAGS) $(OBJ) $(MINILIBX) $(LDFLAGS) -o $(NAME) $(LD)


%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	@make clean -C ./$(MINILIB_PATH)
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)

fclean: clean
	@make fclean -C ./libft
	@make clean -C ./$(MINILIB_PATH)
	$(RM) $(NAME)

re:: fclean
re:: all

asan:: CFLAGS += -fsanitize=address -g3
asan:: LDFLAGS += -fsanitize=address
asan:: re


normi:
	@norminette src inc libft

.PHONY: all clean fclean re normi
