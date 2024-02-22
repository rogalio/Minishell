/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/22 13:09:44 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"

void run_shell(char **envp)
{
    t_token_list *token_list;
    t_pipeline *pipeline;
    int verify;
    char *input;
    char *prompt;

    while (1)
    {
        prompt = display_prompt(); // Générer le prompt personnalisé
        input = readline(prompt); // Utiliser le prompt généré

        if (!input || strcmp(input, "exit") == 0)
        {
            free(input);
            free(prompt);
            break; // Sortir de la boucle si l'utilisateur tape "exit"
        }

        if (input && *input)
            add_history(input); // Ajouter l'entrée à l'historique

        token_list = init_token_list(input);
        //print_token_list(token_list);
        verify = init_syntax_analyzer(token_list);
        if (verify)
        {
            pipeline = parse_rdp(token_list, envp);
           // print_pipeline(pipeline);
            execute_pipeline(pipeline, envp);
        } else
            printf("Error\n");

        free(input);
        free(prompt); // Libérer le prompt après chaque utilisation
        //free_token_list(token_list); // Libérer la liste de tokens
    }
}