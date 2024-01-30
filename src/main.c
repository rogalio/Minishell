/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/30 18:57:24 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "ast.h"
#include "rdp.h"


// probleme a traiter :
// - les sigle quotes dans tokenize
// - faut il gerer les argumenrs ezt leur option dans une seul variable ou independament


void printCommand(t_command *command) {
    if (command == NULL) return;

    printf("Command: %s ", command->cmd);
    for (int i = 0; i < command->arg_count; i++) {
        printf("%s ", command->args[i]);
    }
    printf("\n");
}

void printRedirection(t_redirection *redirection) {
    if (redirection == NULL) return;

    printf("Redirection: %s %s\n", redirection->type, redirection->file);
}

void print_pipeline(t_pipeline *pipeline) {
    if (pipeline == NULL) return;

    for (int i = 0; i < pipeline->command_count; i++) {
        printCommand(pipeline->commands[i]);
        if (i < pipeline->command_count - 1) {
            printf("|\n"); // Indique un pipe entre les commandes
        }
    }

    for (int i = 0; i < pipeline->redirect_count; i++) {
        printRedirection(pipeline->redirects[i]);
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

   t_list *test = tokenize2(" < cat -e hello world | cat -e > file");;
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
