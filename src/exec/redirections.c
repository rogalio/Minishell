/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:51:29 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/30 18:32:14 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "signals.h"
#include "token.h"

int	redirect_heredeocs(t_command *command)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < command->nb_heredocs)
	{
		fd = open(command->heredoc[i]->hdoc_name, O_RDONLY);
		if (fd == -1)
			return (perror("open heredoc file"), 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(command->heredoc[i]->hdoc_name);
		i++;
	}
	return (1);
}

int	redirect_in(t_command *command)
{
	int	fd;

	fd = 0;
	fd = open(command->redirect_in->file, O_RDONLY);
	if (fd == -1)
		return (perror("open input file"), 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redirect_out(t_command *command)
{
	int	fd;

	fd = 0;
	fd = open(command->redirect_out->file, O_WRONLY | O_CREAT | O_TRUNC, \
	0644);
	if (fd == -1)
		return (perror("open output file"), 0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redirect_if_needed(t_command *command)
{
	if (command->heredoc)
	{
		if (!redirect_heredocs(command))
			return (0);
	}
	if (command->redirect_in)
	{
		if (!redirect_in(command))
			return (0);
	}
	if (command->redirect_out)
	{
		if (!redirect_out(command))
			return (0);
	}
	return (1);
}
