/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 16:55:48 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				verify;
	const char		str[] = "echo \"hello \'haha\' \'world\' you \" > file.txt > file3";

	(void)argc;
	(void)argv;
	(void)envp;
	if (!check_regex(str))
		return (1);
	token_list = init_token_list(str);
	print_token_list(token_list);
	printf("\n\n");
	verify = init_syntax_analyzer(token_list);
	if (verify)
	{
		pipeline = parse_rdp(token_list, envp);
		print_pipeline(pipeline);
		execute_pipeline(pipeline, envp);
	}
	else
		return (printf("Error\n"), 1);
	free_token_list(token_list);
	return (0);
}
/*
Tokens :
- Gerer les dbles quotes (a mettre seuls dans la liste de token), verifier
qu'ils sont fermés
==> OK, mais dans gestion d'erreur gérer le cas unclosed quotes

- verifier que seuls des chars/cmdes autorises sont utilises (regex) :
espace, chevrons, quotes (dbles et simples), pipe, dollars, alphanum,
en cas d'erreur, envoyer un msg d'erreur et afficher de nouveau le prompt
pour la commande suivante
==> Ajouter '?'
==> OK

- parse_rdp : avant d'entrer dans la boucle, parcourir, dans differentes
fonction, la liste pour déterminer le nb de cmdes et le nb d'args pour
chaque commande (ajouter dans structure commande le nb d'args ?) ?
- ajouter une structure pour les heredocs
- add_argument_to_command : enlever le realloc
- add_command_to_pipeline : enlever le realloc --> OK

*/
