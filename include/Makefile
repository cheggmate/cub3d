# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/02/18 16:51:43 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC					= -Iinclude
SRC_DIR				= src
HOOKS_DIR			= hooks
PARSER_DIR			= parser
RAYCASTING_DIR		= raycasting
UTILS_DIR			= utils
OBJ_DIR				= obj

# Library folders
LIBFT_DIR			= lib/libft
LIBFT				= ${LIBFT_DIR}/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # Linux specific flags and libs
    MLX_DIR = lib/minilibx-linux
	MLX_INC = -I$(MLX_DIR)
    MLX_LNK = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else
    # macOS (Darwin) specific flags and libs
    MLX_DIR = lib/minilibx_opengl_20191021
	MLX_INC = -I$(MLX_DIR)
    MLX_LNK = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
	

CFLAGS          = -Wall -Wextra -Werror $(INC) $(MLX_INC) -I$(LIBFT_DIR)
NAME				= cub3d

HOOKS_FILES			= $(SRC_DIR)/$(HOOKS_DIR)/movement.c \
						$(SRC_DIR)/$(HOOKS_DIR)/rotation.c
PARSER_FILES		= $(SRC_DIR)/$(PARSER_DIR)/get_colours.c \
						$(SRC_DIR)/$(PARSER_DIR)/get_map.c \
						$(SRC_DIR)/$(PARSER_DIR)/get_textures.c \
						$(SRC_DIR)/$(PARSER_DIR)/parser.c \
						$(SRC_DIR)/$(PARSER_DIR)/validate_map.c
RAYCASTING_FILES	= $(SRC_DIR)/$(RAYCASTING_DIR)/dda.c \
						$(SRC_DIR)/$(RAYCASTING_DIR)/engine.c \
						$(SRC_DIR)/$(RAYCASTING_DIR)/render.c
UTILS_FILES			= $(SRC_DIR)/$(UTILS_DIR)/cleanup_memory.c \
						$(SRC_DIR)/$(UTILS_DIR)/init_game.c \
						$(SRC_DIR)/$(UTILS_DIR)/init_memory.c
					
REQ_SRC				= $(SRC_DIR)/main.c \
					$(UTILS_FILES) $(PARSER_FILES) \
					$(RAYCASTING_FILES) $(HOOKS_FILES)
HEADER				= cub3d.h
OBJ 				= $(REQ_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(info REQ_SRC = $(REQ_SRC))
$(info OBJ = $(OBJ))

# BONUS folders
BONUS_FOLDER	= bonus

# Default target
all: $(LIBFT) $(NAME)

# Compile and archive .o files
$(NAME): $(OBJ) $(LIBFT) $(MLX_DIR)/libmlx.a
	$(CC) $(OBJ) $(LIBFT) $(MLX_LNK) -o $(NAME)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Minilibx
$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)
	
# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .c to .o
# $(BONUS_FOLDER)/%.o : $(BONUS_FOLDER)/%.c
# 	@$(CC) $(FLAG) -c $< -o $@

# BONUS: Compile and archive .o files
# $(NAME_BONUS): $(OBJ_BONUS) $(LIBFT)
# 	$(CC) $(OBJ_BONUS) $(FLAG_BONUS) $(LIBFT) -o $(NAME_BONUS)

# Bonus rules
# bonus:
# 	@$(MAKE) $(NAME_BONUS)

# Clean OBJ files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

# Clean all
fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Used to declare targets that are not actual files but command names
.PHONY: all clean fclean re
