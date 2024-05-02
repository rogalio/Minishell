/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 13:21:49 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredocs.h"

int	read_line(t_heredoc *heredoc, t_minishell *minishell)
{
	char	*line;
	char	*f_line;

	line = NULL;
	f_line = NULL;
	line = readline("> ");
	if (!line && g_exit_signal != 130)
	{
		minishell->error = HDOC_SIGN;
		minishell->exit_status = SUCCESS;
		return (free(line), print_err_msg(&minishell->error), 1);
	}
	if (g_exit_signal == 130 || !ft_strncmp(line, heredoc->delimiter, \
	(ft_strlen(heredoc->delimiter) + 1)))
		return (free(line), minishell->exit_status = SUCCESS, 1);
	f_line = ft_strjoin(line, "\n");
	free (line);
	if (!f_line)
		return (minishell->exit_status = UNEXPEC_ERR, 1);
	if (!handle_expand_quotes(&f_line, minishell->data->env))
		return (free(f_line), minishell->exit_status = UNEXPEC_ERR, 1);
	write(heredoc->fd, f_line, ft_strlen(f_line));
	return (free(f_line), SUCCESS);
}

int	hdoc_child_process(t_heredoc *heredoc, t_minishell *minishell)
{
	init_heredoc_signals();
	while (!read_line(heredoc, minishell))
		;
	return (close(heredoc->fd), exit_process(minishell));
}

int	open_heredoc(t_heredoc *heredoc, t_minishell *minishell)
{
	int	pid;
	int	childval;

	heredoc->fd = open(heredoc->hdoc_name, 578, 0644);
	if (heredoc->fd == -1)
		return (perror("minishell"), 1);
	pid = fork();
	if (pid == -1)
		return (close(heredoc->fd), perror("minishell"), 1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		hdoc_child_process(heredoc, minishell);
	if (waitpid(pid, &childval, 0) == -1)
		return (close(heredoc->fd), perror("minishell"), 1);
	minishell->exit_status = WEXITSTATUS(childval);
	if (minishell->exit_status == 130)
	{
		close(heredoc->fd);
		if (unlink(heredoc->hdoc_name) == -1)
			return (perror("minishell"), UNEXPEC_ERR);
		return (SIGINT_ERR);
	}
	close(heredoc->fd);
	return (minishell->exit_status);
}

int	handle_cmd_heredocs(t_heredoc **heredoc, int nb_hdocs, \
t_minishell *minishell)
{
	int	i;
	int	exit_value;

	i = -1;
	exit_value = 0;
	if (!heredoc)
		return (1);
	while (++i < nb_hdocs)
	{
		exit_value = open_heredoc(heredoc[i], minishell);
		if (exit_value)
			return (minishell->exit_status = exit_value, 0);
	}
	return (1);
}

int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell)
{
	int	i;

	i = -1;
	while (++i < pipeline->command_count)
	{
		if (!handle_cmd_heredocs(pipeline->commands[i]->heredoc, \
		pipeline->commands[i]->nb_heredocs, minishell))
			return (0);
	}
	return (1);
}
