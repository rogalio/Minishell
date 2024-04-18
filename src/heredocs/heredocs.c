/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/18 13:36:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredocs.h"

int	hdoc_child_process(t_heredoc *heredoc)
{
	
}

int	open_heredoc(t_heredoc *heredoc)
{
	int	pid;
	int	childval;

	heredoc->fd = open(heredoc->hdoc_name, 578, 0644);
	if (heredoc->fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (close(heredoc->fd), 0);
	//gerer les signaux heredoc ici;
	if (pid == 0)
		return (hdoc_child_process(heredoc));
	if (waitpid(pid, &childval, 0) == -1)
		return (close(heredoc->fd), 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(heredoc->fd);
		if (unlink(heredoc->hdoc_name) == -1)
			return (0);
		return (0);
	}
	return (1);
}

int	handle_cmd_heredocs(t_heredoc **heredoc, int nb_hdocs)
{
	int	i;

	i = -1;
	if (!heredoc)
		return (1);
	while (++i < nb_hdocs)
	{
		if (!open_heredoc(heredoc[i]))
			return (0);
	}
}

int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell)
{
	int	i;

	i = -1;
	while (++i < pipeline->command_count)
	{
		if (!handle_cmd_heredocs(pipeline->commands[i]->heredoc, \
		pipeline->commands[i]->nb_heredocs))
			return (0);
	}
	return (1);
}
