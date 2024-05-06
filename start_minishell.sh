#!/bin/bash

# Effacer l'écran et déplacer le curseur en haut du terminal
clear
echo -e "\033[H"

# Afficher le message de bienvenue
echo ""
echo -e "\033[0;35m\
		███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗\n\
		████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║\n\
		██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║\n\
		██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║\n\
		██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n\
		╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n\n\
\033[0m\
\033[1;34m\
	                    	  by rmouchel and cabdli\
\033[0m\
\n"

# Lancer le programme minishell
# Vérifier l'argument de la ligne de commande
if [ "$1" == "valgrind" ]; then
	valgrind --suppressions=readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./minishell
else
	./minishell
fi