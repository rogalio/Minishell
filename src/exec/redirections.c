/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:51:29 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 13:23:12 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	redirect_heredocs(t_command *command)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < command->nb_heredocs)
	{
		fd = open(command->heredoc[i]->hdoc_name, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell:", STDERR_FILENO);
			return (perror(command->heredoc[i]->hdoc_name), UNEXPEC_ERR);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (unlink(command->heredoc[i]->hdoc_name) == -1)
			return (perror("minishell"), UNEXPEC_ERR);
		i++;
	}
	return (0);
}

static int	redirect_in(t_command *command)
{
	int	fd;

	fd = 0;
	fd = open(command->redirect_in->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", STDERR_FILENO);
		return (perror(command->redirect_in->file), UNEXPEC_ERR);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redirect_out(t_command *command)
{
	int	fd;
	int	flag;

	fd = 0;
	flag = O_WRONLY | O_CREAT;
	if (!ft_strcmp(command->redirect_out->type, ">>"))
		flag |= O_APPEND;
	else
		flag |= O_TRUNC;
	fd = open(command->redirect_out->file, flag, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", STDERR_FILENO);
		return (perror(command->redirect_out->file), UNEXPEC_ERR);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_if_needed(t_command *command)
{
	if (command->heredoc)
	{
		if (redirect_heredocs(command))
			return (1);
	}
	if (command->redirect_in)
	{
		if (redirect_in(command))
			return (1);
	}
	if (command->redirect_out)
	{
		if (redirect_out(command))
			return (1);
	}
	return (0);
}
