/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/30 19:02:17 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"



t_command *parseCommand(t_list **currentToken) {
    t_command *command = malloc(sizeof(t_command));
    command->args = malloc(sizeof(char *) * MAX_ARGS);
    command->arg_count = 0;

    while (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_WORD) {
        t_token *token = (t_token *)(*currentToken)->content;
        if (command->arg_count == 0) {
            command->cmd = ft_strdup(token->value);
        } else {
            command->args[command->arg_count - 1] = ft_strdup(token->value);
        }
        command->arg_count++;
        *currentToken = (*currentToken)->next;
    }

    command->args[command->arg_count - 1] = NULL; // Terminez le tableau d'arguments par NULL
    return command;
}

int isRedirection(t_list *currentToken) {
    return currentToken && ((t_token *)(currentToken)->content)->type == TOKEN_REDIRECT;
}

int isPipe(t_list *currentToken) {
    return currentToken && ((t_token *)(currentToken)->content)->type == TOKEN_PIPE;
}

t_redirection *parseRedirection(t_list **currentToken) {
    if (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_REDIRECT) {
        t_redirection *redirect = malloc(sizeof(t_redirection));
        redirect->type = ft_strdup(((t_token *)(*currentToken)->content)->value);
        *currentToken = (*currentToken)->next;

        if (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_WORD) {
            redirect->file = ft_strdup(((t_token *)(*currentToken)->content)->value);
            *currentToken = (*currentToken)->next;
        }

        return redirect;
    }

    return NULL;
}

void parsePipe(t_list **currentToken) {
    if (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_PIPE) {
        printf("%s ", ((t_token *)(*currentToken)->content)->value);
        *currentToken = (*currentToken)->next;
    }
    // Analyser la commande suivant immédiatement le pipe
    if (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_WORD) {
        parseCommand(currentToken);
    }
}




t_pipeline *parse_rdp(t_list *tokens) {
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->commands = malloc(sizeof(t_command *) * MAX_ARGS);
    pipeline->redirects = malloc(sizeof(t_redirection *) * MAX_ARGS);
    pipeline->command_count = 0;
    pipeline->redirect_count = 0;

    t_command *currentCommand = NULL;

    while (tokens != NULL) {
        t_token *token = (t_token *)tokens->content;
        switch (token->type) {
            case TOKEN_WORD:
                // Si aucune commande en cours, commencez-en une nouvelle
                if (!currentCommand) {
                    currentCommand = parseCommand(&tokens);
                    pipeline->commands[pipeline->command_count++] = currentCommand;
                } else {
                    // Sinon, ajoutez le mot à la commande actuelle
                    currentCommand->args[currentCommand->arg_count++] = ft_strdup(token->value);
                    tokens = tokens->next;
                }
                break;
            case TOKEN_PIPE:
                // Terminer la commande actuelle et réinitialiser pour la prochaine commande
                currentCommand = NULL;
                tokens = tokens->next;
                break;
            case TOKEN_REDIRECT: {
                // Analyser la redirection et l'associer à la commande actuelle
                t_redirection *redirect = parseRedirection(&tokens);
                pipeline->redirects[pipeline->redirect_count++] = redirect;
                break;
            }
        }
    }

    return pipeline;
}
