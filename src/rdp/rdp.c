/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 11:36:01 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"


// Utilitaires de gestion de mémoire et d'erreur (à implémenter)
void *safe_malloc(size_t size);

char *safe_strdup(const char *s);

void free_command(t_command *cmd)
{
    free(cmd->cmd);
    for (int i = 0; i < cmd->arg_count; i++)
    {
        free(cmd->args[i]);
    }
    free(cmd->args);
    if (cmd->redirect)
    {
        free(cmd->redirect->type);
        free(cmd->redirect->file);
        free(cmd->redirect);
    }
    free(cmd);
}

void free_pipeline(t_pipeline *pipeline)
{
    for (int i = 0; i < pipeline->command_count; i++)
    {
        free_command(pipeline->commands[i]);
    }
    free(pipeline->commands);
    free(pipeline->pipe_positions);
    free(pipeline);
}


void add_command_to_pipeline(t_pipeline *pipeline, t_command *command) {
    pipeline->commands = realloc(pipeline->commands, sizeof(t_command *) * (pipeline->command_count + 1));
    if (!pipeline->commands) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    pipeline->commands[pipeline->command_count++] = command;
}


t_command *create_command(char *cmd) {
    t_command *command = malloc(sizeof(t_command));
    command->cmd = ft_strdup(cmd);
    command->args = NULL;
    command->arg_count = 0;
    command->redirect = NULL;
    return command;
}

void add_argument_to_command(t_command *command, char *arg) {
    command->args = realloc(command->args, sizeof(char *) * (command->arg_count + 1));
    if (!command->args) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    command->args[command->arg_count++] = ft_strdup(arg);
}



void handle_token(t_list **token_list, t_pipeline *pipeline, t_command **current_command)
{
    t_token *token = (t_token *)(*token_list)->content;
    if (token->type == TOKEN_PIPE)
    {
        if (*current_command) {
            (*current_command)->is_piped = 1; // Indique que cette commande est suivie d'un pipe
            add_command_to_pipeline(pipeline, *current_command);
            *current_command = NULL;
        } else {
            fprintf(stderr, "Syntax error: pipe without preceding command\n");
            exit(EXIT_FAILURE);
        }
        *token_list = (*token_list)->next;
        return;
    }
    if (token->type == TOKEN_REDIRECT)
    {
        if (!*current_command) {
            fprintf(stderr, "Syntax error: redirection without command\n");
            exit(EXIT_FAILURE);
        }
        if ((*token_list)->next == NULL) {
            fprintf(stderr, "Syntax error: redirection without file\n");
            exit(EXIT_FAILURE);
        }
        t_token *file_token = (t_token *)(*token_list)->next->content;
        if (file_token->type != TOKEN_WORD) {
            fprintf(stderr, "Syntax error: redirection without file\n");
            exit(EXIT_FAILURE);
        }
        if (!(*current_command)->redirect) {
            (*current_command)->redirect = malloc(sizeof(t_redirection));
            (*current_command)->redirect->type = ft_strdup(token->value);
            (*current_command)->redirect->file = ft_strdup(file_token->value);
        } else {
            fprintf(stderr, "Syntax error: multiple redirections\n");
            exit(EXIT_FAILURE);
        }
        *token_list = (*token_list)->next;
        *token_list = (*token_list)->next;
        return;
    }
    if (!*current_command) {
        *current_command = create_command(token->value);
    } else {
        add_argument_to_command(*current_command, token->value);
    }
    *token_list = (*token_list)->next;
}

t_pipeline *parse_rdp(t_list *tokens) {
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->commands = NULL;
    pipeline->command_count = 0;
    pipeline->pipe_positions = NULL;
    pipeline->pipe_count = 0;
    t_command *current_command = NULL;
    while (tokens) {
        handle_token(&tokens, pipeline, &current_command);
    }
    if (current_command) {
        add_command_to_pipeline(pipeline, current_command);
    }
    return pipeline;
}
