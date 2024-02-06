/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_token_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:46:02 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 12:53:50 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void init_redirection(t_redirection **redirect, const char *type, const char *file)
{
    t_redirection *rd = *redirect;
    if (!rd)
    {
        rd = malloc(sizeof(t_redirection));
        if (!rd)
        {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }
        rd->type = NULL;
        rd->file = NULL;
        *redirect = rd;
    } else
    {
        free(rd->type);
        free(rd->file);
    }
    rd->type = ft_strdup(type);
    rd->file = ft_strdup(file);
}

void handle_redirection(t_token_list **tokens, t_command *command)
{
    char *type;
    char *file;

    type = (*tokens)->token->value;
    *tokens = (*tokens)->next;
    file = (*tokens)->token->value;

    if (ft_strcmp(type, "<") == 0 || ft_strcmp(type, "<<") == 0)
        init_redirection(&command->redirect_in, type, file);
    else if (ft_strcmp(type, ">") == 0 || ft_strcmp(type, ">>") == 0)
        init_redirection(&command->redirect_out, type, file);
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

