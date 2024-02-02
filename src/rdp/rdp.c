/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 20:27:38 by rogalio          ###   ########.fr       */
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
        fprintf(stderr, "Allocation error in add_command_to_pipeline\n");
        free_pipeline(pipeline);
        exit(EXIT_FAILURE);
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
    int count;
    char **new_args;

    count = count_args(command);
    new_args = allocate_new_args(command, count + 1);
    if (!new_args)
    {
        fprintf(stderr, "Allocation error in add_argument_to_command\n");
        free_command(command);
        exit(EXIT_FAILURE);
    }
    command->args = new_args;
    append_argument(command->args, count, arg);

}

void handle_redirection(t_list **token_list, t_command *cmd)
{
    t_token *token;
    t_token *file_token;

    token = (t_token *)(*token_list)->content;
    cmd->redirect = malloc(sizeof(t_redirection));
    if (!cmd->redirect)
    {
        fprintf(stderr, "Allocation error in handle_redirection\n");
        free_command(cmd);
        exit(EXIT_FAILURE);
    }

    cmd->redirect->type = ft_strdup(token->value);
    *token_list = (*token_list)->next;
    file_token = (t_token *)(*token_list)->content;
    cmd->redirect->file = ft_strdup(file_token->value);
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

void handle_token(t_list **token_list, t_pipeline *pipeline, t_command **current_command)
{
    t_token *token;

    token = (t_token *)(*token_list)->content;
    if (token->type == TOKEN_PIPE)
        handle_pipe(pipeline, current_command);
    else if (token->type == TOKEN_REDIRECT)
        handle_redirection(token_list, *current_command);
    else
        handle_word(current_command, token->value);
    *token_list = (*token_list)->next;
}


t_pipeline *parse_rdp(t_list *tokens)
{
    t_pipeline *pipeline;
    t_command *last_command;

    pipeline = init_pipeline();
    if (!pipeline)
        return NULL;
    last_command = NULL;
    while (tokens)
        handle_token(&tokens, pipeline, &last_command);
    if (last_command)
        add_command_to_pipeline(pipeline, last_command);
    return pipeline;
}