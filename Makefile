# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:54:57 by jotong            #+#    #+#              #
#    Updated: 2026/02/18 16:38:19 by jotong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC				= -Iinclude
SRC_DIR			= src
BUILTINS_DIR	= builtins

# Library folders
LIBFT_DIR		= lib/libft
LIBFT			= ${LIBFT_DIR}/libft.a

OBJ_DIR			= obj
FLAG			= -Wall -Wextra -Werror -I$(LIBFT_DIR) $(INC)
NAME			= cub3d

BUILTINS_FILES	= $(SRC_DIR)/$(BUILTINS_DIR)/cd.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/echo.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/env.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/env2.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/env3.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/env4.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/builtin-utils.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/builtin-utils2.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/builtin-utils3.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/builtin-utils4.c \
					$(SRC_DIR)/$(BUILTINS_DIR)/builtin-utils5.c
REQ_SRC			:= $(SRC_DIR)/main.c \
					$(HISTORY_FILES) $(EXECUTOR_FILES) \
					$(UTILS_FILES)
HEADER			= cub3d.h
OBJ 			= $(REQ_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(info REQ_SRC = $(REQ_SRC))
$(info OBJ = $(OBJ))

# BONUS folders
BONUS_FOLDER	= bonus

# Default target
all: $(LIBFT) $(NAME)

# Compile and archive .o files
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(FLAG) $(LIBFT) -lreadline -o $(NAME)

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
