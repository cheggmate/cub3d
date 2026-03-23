# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/03/23 12:32:58 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude -Ilib/libft -Ilib/minilibx-linux

# Paths
LIBFT       = lib/libft/libft.a
MLX_PATH    = lib/minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx.a

# Source Files
SRC         = src/main.c \
              src/utils/array_utils.c src/utils/cleanup_memory.c \
			  src/utils/cleanup_memory2.c \
              src/utils/init_game.c src/utils/init_memory.c \
              src/parser/get_colours.c src/parser/get_map.c \
              src/parser/get_textures.c src/parser/parser.c \
              src/parser/path_check.c src/parser/validate_map.c \
			  src/parser/get_tmp_map.c \
              src/raycasting/dda.c src/raycasting/engine.c \
              src/raycasting/render.c \
              src/hooks/movement.c src/hooks/rotation.c

OBJ_DIR     = obj
OBJ         = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # Linux Flags
    MLX_PATH = ./lib/minilibx-linux
    MLX_LIB  = $(MLX_PATH)/libmlx.a
    MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
else
    # macOS Flags
    MLX_PATH = ./lib/minilibx_opengl_20191021
    MLX_LIB  = $(MLX_PATH)/libmlx.a
    MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

$(NAME): $(OBJ) $(LIBFT)
	@make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make bonus -C lib/libft

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C lib/libft clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re