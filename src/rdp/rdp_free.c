/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:07:45 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/02 16:01:21 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"


void free_redirection(t_redirection *redirection)
{
    if (!redirection)
        return;
    free(redirection->type);
    free(redirection->file);
    free(redirection);
}

void free_heredoc(t_heredoc *heredoc)
{
    int i;

    if (!heredoc)
        return;
    free(heredoc->type);
    if (heredoc->delimiter)
    {
        i = 0;
        while (i < heredoc->nb_heredocs)
        {
            free(heredoc->delimiter[i]);
            i++;
        }
        free(heredoc->delimiter);
    }
    free(heredoc);
}

void free_command(t_command *command)
{
    int i;

    if (!command)
        return;
    if (command->args)
    {
        i = 0;
        while (i < command->args_count)
        {
            free(command->args[i]);
            i++;
        }
        free(command->args);
    }
    free_redirection(command->redirect_in);
    free_redirection(command->redirect_out);
    free_heredoc(command->heredoc);
    free(command);
}

void free_commands(t_command **commands, int command_count)
{
    int i;

    if (!commands)
        return;
    i = 0;
    while (i < command_count)
    {
        free_command(commands[i]);
        i++;
    }
    free(commands);
}

void free_pipeline(t_pipeline *pipeline)
{
		if (!pipeline)
				return;
		free_commands(pipeline->commands, pipeline->command_count);
		free(pipeline);
}