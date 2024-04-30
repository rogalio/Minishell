/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:04:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/26 17:06:39 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	*print_redirection_in(t_redirection *redirection)
{
	if (!redirection)
		return (printf("No redirection in\n"), NULL);
	printf("Redirection in:\n");
	printf("Type: %s\n", redirection->type);
	printf("File: %s\n", redirection->file);
	return (NULL);
}

void	*print_redirection_out(t_redirection *redirection)
{
	if (!redirection)
		return (printf("No redirection out\n"), NULL);
	printf("Redirection out:\n");
	printf("Type: %s\n", redirection->type);
	printf("File: %s\n", redirection->file);
	return (NULL);
}

void	*print_heredoc(t_heredoc **heredoc, int nb_heredocs)
{
	int	i;

	i = -1;
	if (!heredoc)
		return (printf("No heredoc\n"), NULL);
	printf("Heredoc:\n");
	printf("Number of heredocs : %d\n", nb_heredocs);
	while (++i < nb_heredocs)
	{
		printf("Heredoc %d:\n", i + 1);
		printf("Heredoc name: %s\n", heredoc[i]->hdoc_name);
		printf("Heredoc delimiter: %s\n\n", heredoc[i]->delimiter);
	}
	return (NULL);
}

void	*print_command(t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (printf("Empty command\n"), NULL);
	printf("Command with %d argument(s):\n", cmd->args_count);
	while (cmd->args && cmd->args[++i])
		printf("Argument %d: %s$\n", i + 1, cmd->args[i]);
	print_redirection_in(cmd->redirect_in);
	print_redirection_out(cmd->redirect_out);
	print_heredoc(cmd->heredoc, cmd->nb_heredocs);
	printf("\n");
	return (NULL);
}

void	*print_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = -1;
	if (!pipeline)
		return (printf("Empty pipeline\n"), NULL);
	printf("Pipeline with %d command(s):\n", pipeline->command_count);
	while (++i < pipeline->command_count)
	{
		printf("Command %d:\n", i + 1);
		print_command(pipeline->commands[i]);
		printf("\n");
	}
	return (NULL);
}
