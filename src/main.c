/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 19:03:28 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"


// probleme a traiter :
// - les sigle quotes dans tokenize
// - faut il gerer les argumenrs ezt leur option dans une seul variable ou independament


void print_redirection(t_redirection *redirect) {
    if (redirect) {
        printf("Redirection type: %s, file: %s\n", redirect->type, redirect->file);
    } else {
        printf("No redirection\n");
    }
}

void print_command(t_command *cmd) {
    if (!cmd) {
        printf("Empty command\n");
        return;
    }

    printf("Command: ");
    for (int i = 0; cmd->args && cmd->args[i]; i++) {
        printf("%s ", cmd->args[i]);
    }
    printf("\n");

    print_redirection(cmd->redirect);
}

void print_pipeline(t_pipeline *pipeline) {
    if (!pipeline) {
        printf("Empty pipeline\n");
        return;
    }

    printf("Pipeline with %d command(s):\n", pipeline->command_count);
    for (int i = 0; i < pipeline->command_count; i++) {
        printf("Command %d:\n", i + 1);
        print_command(pipeline->commands[i]);
        printf("\n");
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

    t_list *test = tokenize(" cat -e  | grep -e ""hello"" << file.txt  | wc -l");
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
