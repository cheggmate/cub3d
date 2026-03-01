# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/03/01 13:38:34 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR         = src

LIBFT_DIR       = lib/libft
LIBFT           = ${LIBFT_DIR}/libft.a

OBJ_DIR         = obj

MLX_FLAGS       = -lmlx -lXext -lX11 -lm
FLAG            = -Wall -Wextra -Werror -I$(LIBFT_DIR) $(INC)
NAME            = cub3d

# Organized by the subdirectories in your src folder
HOOKS_FILES     = $(SRC_DIR)/hooks/movement.c \
                  $(SRC_DIR)/hooks/rotation.c

PARSER_FILES    = $(SRC_DIR)/parser/get_colors.c \
                  $(SRC_DIR)/parser/get_map.c \
                  $(SRC_DIR)/parser/get_textures.c \
                  $(SRC_DIR)/parser/parser.c \
                  $(SRC_DIR)/parser/validate_map.c

RAY_FILES       = $(SRC_DIR)/raycasting/dda.c \
                  $(SRC_DIR)/raycasting/engine.c \
                  $(SRC_DIR)/raycasting/render.c

UTILS_FILES     = $(SRC_DIR)/utils/array_utils.c \
                  $(SRC_DIR)/utils/cleanup_memory.c \
                  $(SRC_DIR)/utils/init_game.c \
                  $(SRC_DIR)/utils/init_memory.c

# Combine all source files
REQ_SRC         = $(SRC_DIR)/main.c \
                  $(HOOKS_FILES) \
                  $(PARSER_FILES) \
                  $(RAY_FILES) \
                  $(UTILS_FILES)

OBJ             = $(REQ_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(LIBFT) $(NAME)

# Compile the final executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(FLAG) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c to .o and create necessary subdirectories in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

# Clean OBJ files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Clean all
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
