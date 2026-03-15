# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/03/15 16:30:05 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR         = src
INC_DIR         = include
LIB_DIR         = lib
LIBFT_DIR       = lib/libft
LIBFT           = ${LIBFT_DIR}/libft.a
MINILIBX_FOLDER = lib/minilibx-linux
MINILIBX        = ${MINILIBX_FOLDER}/libmlx.a
LIBS_DIR        = -L$(LIB_DIR) -llibft -lminilibx-linux
LIBS_HEADERS    = -I$(LIBFT_DIR) -I$(MINILIBX_FOLDER) -I$(INC_DIR)
OBJ_DIR         = obj
MLX_FLAGS       = -lmlx -lXext -lX11 -lm
FLAG            = -Wall -Wextra -Werror $(LIBS_HEADERS)
NAME            = cub3d

HOOKS_FILES     = $(SRC_DIR)/hooks/movement.c \
                  $(SRC_DIR)/hooks/rotation.c

PARSER_FILES    = $(SRC_DIR)/parser/get_colours.c \
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

REQ_SRC         = $(SRC_DIR)/main.c \
                  $(HOOKS_FILES) \
                  $(PARSER_FILES) \
                  $(RAY_FILES) \
                  $(UTILS_FILES)

OBJ             = $(REQ_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(MINILIBX_FOLDER)
	$(CC) $(OBJ) $(LIBFT) $(LIBS_DIR) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MINILIBX_FOLDER) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re