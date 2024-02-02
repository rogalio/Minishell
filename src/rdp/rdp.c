/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 17:01:17 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"

void free_command(t_command *cmd) {
    if (!cmd) return;
    for (int i = 0; cmd->args && cmd->args[i]; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    if (cmd->redirect) {
        free(cmd->redirect->type);
        free(cmd->redirect->file);
        free(cmd->redirect);
    }
    free(cmd);
}

void free_pipeline(t_pipeline *pipeline) {
    if (!pipeline) return;
    for (int i = 0; i < pipeline->command_count; i++) {
        free_command(pipeline->commands[i]);
    }
    free(pipeline->commands);
    free(pipeline);
}

t_command *create_command(void) {
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;
    cmd->args = NULL;
    cmd->redirect = NULL;
    return cmd;
}

void add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd) {
    pipeline->commands = realloc(pipeline->commands, sizeof(t_command *) * (pipeline->command_count + 1));
    if (!pipeline->commands) {
        free_pipeline(pipeline);
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    pipeline->commands[pipeline->command_count++] = cmd;
}

void add_argument_to_command(t_command *command, char *arg) {
    int arg_count;
    for (arg_count = 0; command->args && command->args[arg_count]; arg_count++);

    size_t new_size = sizeof(char *) * (arg_count + 2);
    command->args = realloc(command->args, new_size);
    if (!command->args) {
        free_command(command);
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    command->args[arg_count] = ft_strdup(arg);
    command->args[arg_count + 1] = NULL;
}

void handle_redirection(t_list **token_list, t_command *cmd) {
    t_token *token = (t_token *)(*token_list)->content;
    if (!cmd->redirect) {
        cmd->redirect = malloc(sizeof(t_redirection));
        if (!cmd->redirect) {
            fprintf(stderr, "Allocation error\n");
            exit(EXIT_FAILURE);
        }
        cmd->redirect->type = ft_strdup(token->value);
        *token_list = (*token_list)->next; // Move to file token
        t_token *file_token = (t_token *)(*token_list)->content;
        if (!file_token || file_token->type != TOKEN_WORD) {
            fprintf(stderr, "Syntax error: redirection without file\n");
            exit(EXIT_FAILURE);
        }
        cmd->redirect->file = ft_strdup(file_token->value);
    } else {
        fprintf(stderr, "Syntax error: multiple redirections for a command\n");
        exit(EXIT_FAILURE);
    }
}

void handle_token(t_list **token_list, t_pipeline *pipeline, t_command **current_command) {
    t_token *token = (t_token *)(*token_list)->content;
    if (token->type == TOKEN_PIPE) {
        if (!*current_command || !(*current_command)->args) {
            fprintf(stderr, "Syntax error: pipe without preceding command\n");
            exit(EXIT_FAILURE);
        }
        add_command_to_pipeline(pipeline, *current_command);
        *current_command = create_command();
        *token_list = (*token_list)->next;
        return;
    }
    if (token->type == TOKEN_REDIRECT) {
        handle_redirection(token_list, *current_command);
        *token_list = (*token_list)->next;
        return;
    }
    if (!*current_command) {
        *current_command = create_command();
    }
    add_argument_to_command(*current_command, token->value);
    *token_list = (*token_list)->next;
}

t_pipeline *parse_rdp(t_list *tokens) {
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline) return NULL;
    pipeline->commands = NULL;
    pipeline->command_count = 0;

    t_command *current_command = NULL;
    while (tokens) {
        handle_token(&tokens, pipeline, &current_command);
    }
    if (current_command && current_command->args) {
        add_command_to_pipeline(pipeline, current_command);
    } else {
        free_command(current_command);
    }
    return pipeline;
}