/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:07:45 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 18:53:21 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	free_command(t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd->args && cmd->args[++i])
		free(cmd->args[i]);
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

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = -1;
	if (!pipeline)
		return ;
	while (++i < pipeline->command_count)
		free_command(pipeline->commands[i]);
	free(pipeline->commands);
	free(pipeline);
}
