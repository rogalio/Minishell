# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 19:31:50 by cabdli            #+#    #+#              #
#    Updated: 2024/05/07 10:53:58 by cabdli           ###   ########.fr        #
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

NAME = libft.a

SRCS = ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isspace.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strndup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_printf.c\
		ft_printf_utils.c\
		ft_print_uitoa.c\
		ft_print_hex.c\
		ft_print_ptr.c\
		get_next_line.c\

OBJS = $(SRCS:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS) libft.h
	@echo "$(YELLOW)Making Libft...$(RESET)"
	@ar -cr $(NAME) $(OBJS)
	@echo "$(YELLOW)Libft done !$(RESET)"

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -f $(OBJS)
		
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re