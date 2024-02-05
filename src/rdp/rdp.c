/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 18:28:49 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"

void free_command(t_command *cmd)
{
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

void free_pipeline(t_pipeline *pipeline)
{
    if (!pipeline) return;
    for (int i = 0; i < pipeline->command_count; i++) {
        free_command(pipeline->commands[i]);
    }
    free(pipeline->commands);
    free(pipeline);
}

t_pipeline *init_pipeline()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline)
        return NULL;
    pipeline->commands = NULL;
    pipeline->command_count = 0;
    return pipeline;
}

t_command *create_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;
    cmd->args = NULL;
    cmd->redirect = NULL;
    return cmd;
}

void add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd)
{

    t_command **new_commands = realloc(pipeline->commands, sizeof(t_command *) * (pipeline->command_count + 1));
    if (!new_commands) {
     printf("Allocation error in add_command_to_pipeline\n");
    }

    pipeline->commands = new_commands;
    pipeline->commands[pipeline->command_count++] = cmd;
}

int count_args(t_command *cmd)
{
    int count;

    count = 0;
    while (cmd->args && cmd->args[count])
        count++;
    return count;
}

char **allocate_new_args(t_command *cmd, int new_count)
{
    char **new_args;

    new_args = malloc(sizeof(char *) * (new_count + 1));
    if (!new_args)
    {
        fprintf(stderr, "Allocation error in allocate_news_args\n");
        free_command(cmd);
        exit(EXIT_FAILURE);
    }
    return new_args;
}

void append_argument(char **args, int position, char *arg)
{
    args[position] = ft_strdup(arg);
    args[position + 1] = NULL;
}

void add_argument_to_command(t_command *command, char *arg)
{



    int count = count_args(command);
    char **new_args = allocate_new_args(command, count + 1);
    for (int i = 0; i < count; i++)
    {
        new_args[i] = command->args[i];
    }
    append_argument(new_args, count, arg);
    free(command->args);
    command->args = new_args;
}

void handle_redirection(t_token_list **tokens, t_command *command)
{
    if (!command->redirect)
    {
        command->redirect = malloc(sizeof(t_redirection));
        if (!command->redirect)
        {
            fprintf(stderr, "Allocation error in handle_redirection\n");
            free_command(command);
            exit(EXIT_FAILURE);
        }
    }
    command->redirect->type = ft_strdup((*tokens)->token->value);

    // Avancer pour obtenir le nom du fichier
    *tokens = (*tokens)->next;
    if (*tokens && (*tokens)->token && (*tokens)->token->type == TOKEN_WORD)
        command->redirect->file = ft_strdup((*tokens)->token->value);

}

void handle_word(t_command **current_command, char *word)
{
    if (!*current_command)
        *current_command = create_command();
    add_argument_to_command(*current_command, word);

}

void handle_pipe(t_pipeline *pipeline, t_command **current_command)
{
    if (!*current_command)
        return;
    add_command_to_pipeline(pipeline, *current_command);
    *current_command = create_command();
}

void handle_token(t_token_list **tokens, t_pipeline *pipeline, t_command **current_command)
{
    if ((*tokens)->token->type == TOKEN_WORD)
        handle_word(current_command, (*tokens)->token->value);
    else if ((*tokens)->token->type == TOKEN_REDIRECT)
        handle_redirection(tokens, *current_command);
    else if ((*tokens)->token->type == TOKEN_PIPE)
        handle_pipe(pipeline, current_command);
}


t_pipeline *parse_rdp(t_token_list *tokens)
{
        t_pipeline *pipeline;
        t_command *last_command;

        pipeline = init_pipeline();
        if (!pipeline)
            return NULL;
        last_command = NULL;
        while (tokens)
        {
            handle_token(&tokens, pipeline, &last_command);
            tokens = tokens->next;
        }
        if (last_command)
            add_command_to_pipeline(pipeline, last_command);
        return pipeline;
}