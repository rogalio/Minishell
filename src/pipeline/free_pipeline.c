/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:07:45 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/17 19:19:14 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	free_cmd(t_command *command)
{
	int	i;

	i = -1;
	if (!command)
		return ;
	free_args(command->args, command->args_count);
	free_redirection(command->redirect_in);
	free_redirection(command->redirect_out);
	while (++i < command->nb_heredocs)
	{
		if (!command->heredoc[i])
			break ;
		free_heredoc(command->heredoc[i]);
	}
	free(command);
}

void	free_commands(t_command ***commands, int command_count)
{
	int	i;

	i = -1;
	if (!*commands)
		return ;
	while (++i < command_count)
	{
		if (!*commands[i])
			break ;
		free_cmd(*commands[i]);
		*commands[i] = NULL;
	}
	free(*commands);
	*commands = NULL;
}

void	free_pipeline(t_pipeline **pipeline)
{
	if (!*pipeline)
		return ;
	free_commands(&(*pipeline)->commands, (*pipeline)->command_count);
	free(*pipeline);
	*pipeline = NULL;
}
