/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:07:45 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 17:34:52 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	free_redirection(t_redirection *redirection)
{
	if (!redirection)
		return ;
	if (redirection->type)
		free(redirection->type);
	if (redirection->file)
		free(redirection->file);
	free(redirection);
	redirection = NULL;
}

void	free_heredoc(t_heredoc *heredoc)
{
	int	i;

	i = -1;
	if (!heredoc)
		return ;
	if (heredoc->type)
		free(heredoc->type);
	if (heredoc->delimiter)
	{
		while (++i < heredoc->nb_heredocs)
		{
			if (!heredoc->delimiter[i])
				break ;
			free(heredoc->delimiter[i]);
		}
		free(heredoc->delimiter);
	}
	free(heredoc);
	heredoc = NULL;
}

void	free_args(char **args, int args_count)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (++i < args_count)
	{
		if (!args[i])
			break ;
		free(args[i]);
	}
	free(args);
	args = NULL;
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	free_args(command->args, command->args_count);
	free_redirection(command->redirect_in);
	free_redirection(command->redirect_out);
	free_heredoc(command->heredoc);
	free(command);
	command = NULL;
}

void	free_commands(t_command **commands, int command_count)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (i < command_count)
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
	commands = NULL;
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free_commands(pipeline->commands, pipeline->command_count);
	free(pipeline);
	pipeline = NULL;
}
