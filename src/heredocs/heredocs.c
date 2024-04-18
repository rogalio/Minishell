// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredocs.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
// /*   Updated: 2024/04/18 16:23:23 by cabdli           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "heredocs.h"

// static int	ft_isquote(char c, char quote)
// {
// 	return (c == quote);
// }

// char	*handle_quotes_delimiter(char *delimiter)
// {
// 	int	i;

// 	i = -1;
// 	while (delimiter[++i])
// 	{
// 		if (ft_isquote(delimiter[i], "\'") || ft_isquote(delimiter[i], "\""))
			
// 	}
// }

// int	hdoc_child_process(t_heredoc *heredoc)
// {
// 	//gerer les ignaux chez l'enfant;
// 	heredoc->delimiter = handle_quotes_delimiter(heredoc->delimiter);
// }

// int	open_heredoc(t_heredoc *heredoc)
// {
// 	int	pid;
// 	int	childval;

// 	heredoc->fd = open(heredoc->hdoc_name, 578, 0644);
// 	if (heredoc->fd == -1)
// 		return (0);
// 	pid = fork();
// 	if (pid == -1)
// 		return (close(heredoc->fd), 0);
// 	//gerer les signaux heredoc ici;
// 	if (pid == 0)
// 		return (hdoc_child_process(heredoc));
// 	if (waitpid(pid, &childval, 0) == -1)
// 		return (close(heredoc->fd), 0);
// 	if (WEXITSTATUS(childval) == 130)
// 	{
// 		close(heredoc->fd);
// 		if (unlink(heredoc->hdoc_name) == -1)
// 			return (0);
// 		return (0);
// 	}
// 	return (1);
// }

// int	handle_cmd_heredocs(t_heredoc **heredoc, int nb_hdocs)
// {
// 	int	i;

// 	i = -1;
// 	if (!heredoc)
// 		return (1);
// 	while (++i < nb_hdocs)
// 	{
// 		if (!open_heredoc(heredoc[i]))
// 			return (0);
// 	}
// }

// int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < pipeline->command_count)
// 	{
// 		if (!handle_cmd_heredocs(pipeline->commands[i]->heredoc, \
// 		pipeline->commands[i]->nb_heredocs))
// 			return (0);
// 	}
// 	return (1);
// }
