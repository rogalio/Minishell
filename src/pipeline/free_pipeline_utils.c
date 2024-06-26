/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:10:25 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 22:40:26 by cabdli           ###   ########.fr       */
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

void	free_hdoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	if (heredoc->delimiter)
		free(heredoc->delimiter);
	if (heredoc->hdoc_name)
		free(heredoc->hdoc_name);
	free(heredoc);
	heredoc = NULL;
}

void	free_heredocs(int nb_heredocs, t_heredoc **heredoc)
{
	int	i;

	i = -1;
	if (!heredoc)
		return ;
	while (++i < nb_heredocs)
	{
		if (!heredoc[i])
			break ;
		free_hdoc(heredoc[i]);
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
