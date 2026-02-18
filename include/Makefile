# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/02/18 20:57:15 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC					= -Iinclude
SRC_DIR				= src
HOOKS_DIR			= hooks
PARSER_DIR			= parser
RAYCASTING_DIR		= raycasting
UTILS_DIR			= utils

# Library folders
LIBFT_DIR			= lib/libft
LIBFT				= ${LIBFT_DIR}/libft.a

OBJ_DIR				= obj
FLAG				= -Wall -Wextra -Werror -I$(LIBFT_DIR) $(INC)
NAME				= cub3d

HOOKS_FILES			= $(SRC_DIR)/$(HOOKS_DIR)/movement.c \
						$(SRC_DIR)/$(HOOKS_DIR)/rotation.c
PARSER_FILES		= $(SRC_DIR)/$(PARSER_DIR)/get_colours.c \
						$(SRC_DIR)/$(PARSER_DIR)/get_map.c \
						$(SRC_DIR)/$(PARSER_DIR)/get_textures.c \
						$(SRC_DIR)/$(PARSER_DIR)/parser.c \
						$(SRC_DIR)/$(PARSER_DIR)/validate_map.c
RAYCASTING_FILES	= $(SRC_DIR)/$(PARSER_DIR)/dda.c \
						$(SRC_DIR)/$(PARSER_DIR)/engine.c \
						$(SRC_DIR)/$(PARSER_DIR)/render.c
UTILS_FILES			= $(SRC_DIR)/$(UTILS_DIR)/cd.c  #change the filename
					
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
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(FLAG) $(LIBFT) -o $(NAME)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) -c $< -o $@

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
# @rm -f $(OBJ) $(OBJ_BONUS)

# Clean all
fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Used to declare targets that are not actual files but command names
.PHONY: all clean fclean re
