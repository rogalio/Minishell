# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Nom de l'exécutable
NAME = minishell

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

# Fichiers source (.c) et objet (.o)
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règle par défaut
all: $(NAME)

# Règle pour créer l'exécutable
$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

# Règle pour créer les fichiers objet
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Règle pour compiler la libft
libft:
	make -C $(LIBFT_DIR)

# Règle pour nettoyer les fichiers objet
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

# Règle pour nettoyer tout ce qui peut être regénéré
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Règle pour recompiler
re: fclean all

# Règle pour éviter des conflits avec des fichiers portant le nom des règles
.PHONY: all clean fclean re libft
