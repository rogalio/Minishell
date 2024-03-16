/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/16 01:08:14 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "prompt.h"
#include "utils.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26), 1);
	run_shell(envp);
	return (0);
}
/*

/!\ EXEC : fonction fprintf non autorisée !!!!!

/!\ EXPEND_VAR : fonction realloc pas autorisée

cd - | cat -e : ne fonctionne pas !!!

Handle variable : modifier le cas ou on rencontre un ? par la gestion de
l'exit status

Tokens :
==> Gestion d'erreur : gérer le cas unclosed quotes

- Regex :
en cas d'erreur, envoyer un msg d'erreur et afficher de nouveau le prompt
pour la commande suivante
==> Ajouter '?'$

Heredoc :
- gérer les signaux pdt heredoc
- gérer les expand pdt heredoc
- gérer cmde : cat << EOF > hello_world.txt

*/
