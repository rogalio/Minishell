/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/01 20:16:52 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"


void add_command_to_pipeline(t_pipeline *pipeline, t_command *command) {
    pipeline->commands[pipeline->command_count++] = command;
}

t_command *create_command(char *cmd) {
    t_command *command = malloc(sizeof(t_command));
    command->cmd = ft_strdup(cmd);
    command->args = malloc(sizeof(char *) * MAX_ARGS);
    command->arg_count = 0;
    command->redirect = NULL;
    return command;
}



void handle_token(t_list **token_list, t_pipeline *pipeline, t_command **current_command) {
    t_token *token = (t_token *)(*token_list)->content;

    if (token->type == TOKEN_WORD) {
        if (!*current_command) {
            *current_command = create_command(token->value);
        } else {
            (*current_command)->args[(*current_command)->arg_count++] = ft_strdup(token->value);
        }
    } else if (token->type == TOKEN_REDIRECT) {
        t_redirection *redirect = malloc(sizeof(t_redirection));
        redirect->type = ft_strdup(token->value);
        *token_list = (*token_list)->next;
        redirect->file = ft_strdup(((t_token *)(*token_list)->content)->value);
        if (*current_command) {
            (*current_command)->redirect = redirect;
        }
    } else if (token->type == TOKEN_PIPE) {
        if (*current_command) {
            add_command_to_pipeline(pipeline, *current_command);
            *current_command = NULL;
        }
        pipeline->pipe_positions[pipeline->pipe_count++] = pipeline->command_count;
    }
    *token_list = (*token_list)->next;
}

t_pipeline *parse_rdp(t_list *tokens) {
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->commands = malloc(sizeof(t_command *) * MAX_ARGS);
    pipeline->pipe_positions = malloc(sizeof(int) * MAX_ARGS);
    pipeline->command_count = 0;
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
