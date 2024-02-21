/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/21 22:11:37 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	const char		str[] = "echo \"hello \'haha\' $HOME you \" > file.txt > file3 | cat file3";

	(void)argc;
	(void)argv;
	(void)envp;
	if (!check_regex(str))
		return (1);
	token_list = init_token_list(str);
	print_token_list(token_list);
	printf("\n\n");
	if (init_syntax_analyzer(token_list))
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

- Regex :
en cas d'erreur, envoyer un msg d'erreur et afficher de nouveau le prompt
pour la commande suivante
==> Ajouter '?'

- parse_rdp :
Ajouter un init_heredoc, car dans ce cas on ne supprime pas les type
et file différents, mais on ajoute juste des files (pour sortir des heredocs
successifs) + ajouter une structure heredoc avec un char **file pour enregistrer
les differents mdp de sortie de heredocs + nb de heredocs dans la structure

- Ajouter heredoc dans print_pipeline

*/
