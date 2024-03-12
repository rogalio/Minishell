/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/12 15:19:45 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"

#include "builtins.h"
#include "utils.h"
int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26), 1);
	//display_welcome_message();
	run_shell(envp);
	return (0);
}
/*
Tokens :
- Gerer les dbles quotes (a mettre seuls dans la liste de token), verifier
qu'ils sont fermés
==> OK, mais dans gestion d'erreur gérer le cas unclosed quotes

- Regex :
en cas d'erreur, envoyer un msg d'erreur et afficher de nouveau le prompt
pour la commande suivante
==> Ajouter '?'

- parse_rdp :
Ajouter un init_heredoc, car dans ce cas on ne supprime pas les type
et file différents, mais on ajoute juste des files (pour sortir des heredocs
successifs) + ajouter une structure heredoc avec un char **file pour enregistrer
les differents mdp de sortie de heredocs + nb de heredocs dans la structure
==> OK

- Ajouter heredoc dans print_pipeline ==> OK

*/
