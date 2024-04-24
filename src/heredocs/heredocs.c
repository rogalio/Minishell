/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/24 18:41:23 by cabdli           ###   ########.fr       */
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
		return (free(line), minishell->error = HDOC_SIGN, print_err_msg(&minishell->error), 2);
	if (g_exit_signal == 130 || !ft_strncmp(line, heredoc->delimiter, \
	(ft_strlen(heredoc->delimiter) + 1)))
		return (free(line), 1);
	f_line = ft_strjoin(line, "\n");
	free (line);
	if (!f_line)
		return (1);
	if (!handle_expand_quotes(&f_line, minishell->data->env))
		return (free(f_line), 1);
	write(heredoc->fd, f_line, ft_strlen(f_line));
	return (free(f_line), 0);
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
		return (0);
	pid = fork();
	if (pid == -1)
		return (close(heredoc->fd), 0);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		hdoc_child_process(heredoc, minishell);
	if (waitpid(pid, &childval, 0) == -1)
		return (close(heredoc->fd), 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(heredoc->fd);
		if (unlink(heredoc->hdoc_name) == -1)
			return (0);
		return (130);
	}
	close(heredoc->fd);
	return (1);
}

int	handle_cmd_heredocs(t_heredoc **heredoc, int nb_hdocs, \
t_minishell *minishell)
{
	int	i;

	i = -1;
	if (!heredoc)
		return (1);
	while (++i < nb_hdocs)
	{
		if (!open_heredoc(heredoc[i], minishell))
			return (0);
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
