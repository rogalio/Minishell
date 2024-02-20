/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 13:57:51 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"

#include "builtins.h"

	void print_envp(char **envp){
    int i = 0;
    while (envp[i]) {
        printf("%s\n", envp[i]);
        i++;
    }
	}

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				verify;
	const char		str[] = "echo \"hello \'haha\' \'world\' you \" > file.txt > file3";

	(void)argc;
	(void)argv;

	printf("\n\n");
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
- add_command_to_pipeline : enlever le realloc

*/
