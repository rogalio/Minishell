/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/23 15:41:57 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredocs.h"

// int	hdchild_process(t_data *data, t_rdlist *rd)
// {
// 	signal(SIGINT, ft_handler_heredoc);
// 	rd->file = rmhdquotes(rd->file);
// 	if (!rd->file)
// 		return (cherr_code(UNKNOWN_ERR));
// 	while (!rl_heredoc(data, rd))
// 		;
// 	return (close(rd->fd), exit_all(data, g_err_code));
// }

int	read_line(t_heredoc *heredoc, t_minishell *minishell)
{
	char	*line;
	char	*f_line;

	line = NULL;
	f_line = NULL;
	line = readline("> ");
	if (!line)
		return (free(line), 1);
	if (!ft_strncmp(line, heredoc->delimiter, \
	(ft_strlen(heredoc->delimiter)+ 1)))
		return (free(line), 1);
	f_line = ft_strjoin(line, "\n");
	free (line);
	if (!f_line)
		return (1);
	if (!handle_expand_quotes(&f_line, minishell->data->env))
		return (free(f_line), 1);
	write(heredoc->fd, f_line, ft_strlen(f_line));
	free (f_line);
	return (0);
}


int	hdoc_child_process(t_heredoc *heredoc, t_minishell *minishell)
{
	//gerer les ignaux chez l'enfant;
	while (!read_line(heredoc, minishell))
		;
	close(heredoc->fd);
	free_resources(minishell);
	exit(0);
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
	//gerer les signaux heredoc ici;
	if (pid == 0)
	{
		hdoc_child_process(heredoc, minishell);
		// return (hdoc_child_process(heredoc, minishell), 1);
	}
	if (waitpid(pid, &childval, 0) == -1)
		return (close(heredoc->fd), 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(heredoc->fd);
		if (unlink(heredoc->hdoc_name) == -1)
			return (0);
		g_exit_signal = 130;
		return (0);
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
	printf("in handle_cmd_heredocs nb_hdocs = %d\n\n", nb_hdocs);
	while (++i < nb_hdocs)
	{
		printf("in handle_cmd_heredocs i = %d\n\n", i);
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
