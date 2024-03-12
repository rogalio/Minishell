# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/27 16:09:01 by asoursou          #+#    #+#              #
#    Updated: 2024/03/12 13:41:17 by cabdli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
# Regular
RED = \033[31m
GREEN = \033[32m
YELLOW = \e[0;33m
BLUE = \e[0;34m
PURPLE = \e[0;35m
CYAN = \e[0;36m
WHITE = \e[0;37m
RESET = \033[0m

#Bold
BRED = \e[1;31m	
BGREEN = \e[1;32m	
BYELLOW = \e[1;33m	
BBLUE = \e[1;34m
BPURPLE = \e[1;35m
BCYAN = \e[1;36m
BWHITE = \e[1;37m

BK_PURPLE = \e[45m
BK_GREEN = \e[42m

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
	@echo "$(GREEN)Cleaning done !$(RESET)"

fclean: clean
	@echo "Full cleaning in progress..."
	@make --no-print-directory -C $(FT) $@
	@rm -rf $(NAME)
	@echo "$(GREEN)Full cleaning done !$(RESET)"

re: fclean all

$(BUILD):
	@mkdir $@

$(SUB_DIR): | $(BUILD)
	@mkdir $@

$(BUILD)/%.o: src/%.c | $(SUB_DIR)
	@$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

-include $(DEP)

.PHONY: all bonus clean fclean re
