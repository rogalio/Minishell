/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/01 20:16:45 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"


// probleme a traiter :
// - les sigle quotes dans tokenize
// - faut il gerer les argumenrs ezt leur option dans une seul variable ou independament


void printCommand(t_command *command) {
    if (!command) return;

    printf("Command: %s\n", command->cmd);
    printf("Arguments: ");
    for (int i = 0; i < command->arg_count; i++) {
        printf("%s ", command->args[i]);
    }
    printf("\n");

    if (command->redirect) {
        printf("Redirection: %s %s\n", command->redirect->type, command->redirect->file);
    }
    printf("\n");
}

void print_pipeline(t_pipeline *pipeline) {
    if (!pipeline) return;

    for (int i = 0; i < pipeline->command_count; i++) {
        printCommand(pipeline->commands[i]);
    }
    printf("Pipe positions: ");
    for (int i = 0; i < pipeline->pipe_count; i++) {
        printf("%d ", pipeline->pipe_positions[i]);
    }

    printf("\n");
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

   t_list *test = tokenize("wc -l < out.txt | ls -l >> out.txt ");
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
