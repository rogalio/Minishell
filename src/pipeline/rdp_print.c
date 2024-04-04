/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:04:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 13:50:12 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "token.h"


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

void	*print_heredoc(t_heredoc *heredoc)
{
	int	i;

	i = -1;
	if (!heredoc)
		return (printf("No heredoc\n"), NULL);
	printf("Heredoc:\n");
	printf("Number of heredocs : %d\n", heredoc->nb_heredocs);
	printf("Type: %s\n", heredoc->type);
	while (heredoc->delimiter && heredoc->delimiter[++i])
		printf("Heredoc delimiter %d: %s\n", i + 1, heredoc->delimiter[i]);
	return (NULL);
}
/*
int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
*/

void	*print_command(t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (printf("Empty command\n"), NULL);
	printf("Command with %d argument(s):\n", cmd->args_count);
	while (cmd->args && cmd->args[++i])
		printf("Argument %d: %s\n", i + 1, cmd->args[i]);
	print_redirection_in(cmd->redirect_in);
	print_redirection_out(cmd->redirect_out);
	print_heredoc(cmd->heredoc);
	printf("\n");
	return (NULL);
}

void	*print_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = -1;
	if (!pipeline)
		return (printf("Empty pipeline\n"), NULL);
	printf("Pipeline with %d command(s):\n\n", pipeline->command_count);
	while (++i < pipeline->command_count)
	{
		printf("Command %d:\n", i + 1);
		print_command(pipeline->commands[i]);
	}
	return (NULL);
}
