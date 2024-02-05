/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:07:45 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 19:08:04 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void free_command(t_command *cmd)
{
    if (!cmd) return;
    for (int i = 0; cmd->args && cmd->args[i]; i++)
    {
        free(cmd->args[i]);
    }
    free(cmd->args);
    if (cmd->redirect_in)
    {
        free(cmd->redirect_in->type);
        free(cmd->redirect_in->file);
        free(cmd->redirect_in);
    }
    if (cmd->redirect_out)
    {
        free(cmd->redirect_out->type);
        free(cmd->redirect_out->file);
        free(cmd->redirect_out);
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