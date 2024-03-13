# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/27 16:09:01 by asoursou          #+#    #+#              #
#    Updated: 2024/03/13 16:50:54 by cabdli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
# Regular
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

#Bold
BRED = \033[1;31m	
BGREEN = \033[1;32m	
BYELLOW = \033[1;33m	
BBLUE = \033[1;34m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BWHITE = \033[1;37m

BK_PURPLE = \033[45m
BK_GREEN = \033[42m

# COMPILATION
FT		:= libft
CC		:= clang
CFLAGS	:= -Wall -Wextra -Werror
DFLAGS	= -MP -MMD -MF $(BUILD)/$*.d -MT $@
IFLAGS	:= -isystem./$(FT)/inc -I./include -I./inc/private
LDFLAGS	:= -L./$(FT) -lft -lreadline

# DIRECTORIES
BUILD	:= .build
SUB_DIR	:= $(wildcard src/*/.)
SUB_DIR	:= $(SUB_DIR:src/%/.=$(BUILD)/%/)

# FILES
NAME	:= minishell
SRC		:= $(wildcard src/*/*.c) $(wildcard src/*.c)
SRC		:= $(SRC:src/%=%)
DEP		:= $(SRC:%.c=$(BUILD)/%.d)
OBJ		:= $(SRC:%.c=$(BUILD)/%.o)

$(NAME): $(OBJ)
	@echo "$(PURPLE)Making minishell...$(RESET)"
	@make --no-print-directory -j -C $(FT)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)Minishell done !$(RESET)"
	@./start_minishell.sh

all: $(NAME)

# Cible pour exécuter le script de démarrage
run_minishell:
	./start_minishell.sh

bonus: all

clean:
	@echo "Cleaning in progress..."
	@make --no-print-directory -C $(FT) $@
	@rm -rf $(BUILD)
	@echo "$(YELLOW)Cleaning done !$(RESET)"

fclean: clean
	@echo "Full cleaning in progress..."
	@make --no-print-directory -C $(FT) $@
	@rm -rf $(NAME)
	@echo "$(YELLOW)Full cleaning done !$(RESET)"

re: fclean all

$(BUILD):
	@mkdir $@

$(SUB_DIR): | $(BUILD)
	@mkdir $@

$(BUILD)/%.o: src/%.c | $(SUB_DIR)
	@$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

-include $(DEP)

.PHONY: all bonus clean fclean re
