/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 19:20:54 by cabdli           ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	(void)envp;
	token_list = init_token_list("echo hello > file.txt > file3");
	print_token_list(token_list);
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
qu'ils sont fermes
- verifier que seuls des chars/cmdes autorises sont utilises (regex)
==> chevrons, quotes (dbles et simples), pipe, dollars, alphanum

- add_argument_to_command : enlever le realloc
- add_command_to_pipeline : enlever le realloc

- parse_rdp : avant d'entrer dans la boucle, parcourir, dans differentes
fonction, la liste pour déterminer le nb de cmdes et le nb d'args pour
chaque commande (ajouter dans structure commande le nb d'args ?) ?
- ajouter une structure pour les heredocs

- Faire un split pour éliminer les espaces, parcourir plus facilement
le tableau et malloc directement ?
*/
