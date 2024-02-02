/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 11:40:27 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"


// probleme a traiter :
// - les sigle quotes dans tokenize
// - faut il gerer les argumenrs ezt leur option dans une seul variable ou independament


// Fonction pour afficher les détails d'une redirection
void print_redirection(t_redirection *redirect) {
    if (redirect) {
        printf("Redirection: %s %s\n", redirect->type, redirect->file);
    }
}

// Fonction pour afficher les détails d'une commande
void print_command(t_command *command) {
    if (command) {
        printf("Command: %s\n", command->cmd);
        for (int i = 0; i < command->arg_count; i++) {
            printf("Argument %d: %s\n", i, command->args[i]);
        }
        print_redirection(command->redirect);
        if (command->is_piped) {
            printf("This command is piped.\n");
        }
    }
}

// Fonction pour afficher les détails d'un pipeline
void print_pipeline(t_pipeline *pipeline) {
    if (pipeline) {
        printf("Pipeline:\n");
        for (int i = 0; i < pipeline->command_count; i++) {
            printf("Command %d:\n", i);
            print_command(pipeline->commands[i]);
            if (i < pipeline->command_count - 1) {
                printf("---\n");
            }
        }
    }
}


int		main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;


    /*
        int verify = validate_tokens(tokenize2(" cat -e 'hello world' "));
    if (verify == 1)
        printf("valid\n");
    else
        printf("invalid\n");

    */

    t_list *test = tokenize(" cat -e  | grep -e ""hello"" > file.txt");
    t_pipeline *pipeline = parse_rdp(test);
    print_pipeline(pipeline);





   /*

      while (test)
   {
       t_token *token = (t_token *)test->content;
       printf("type : %d  ", token->type);
       printf("value : %s\n", token->value);
       test = test->next;
   }



   */

    return (0);
}
