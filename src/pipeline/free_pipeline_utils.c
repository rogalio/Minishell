/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:10:25 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/11 15:12:27 by cabdli           ###   ########.fr       */
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

void	free_heredoc(t_heredoc *heredoc)
{
	int	i;

	i = -1;
	if (!heredoc)
		return ;
	if (heredoc->type)
		free(heredoc->type);
	if (heredoc->delimiter)
	{
		while (++i < heredoc->nb_heredocs)
		{
			if (!heredoc->delimiter[i])
				break ;
			free(heredoc->delimiter[i]);
		}
		free(heredoc->delimiter);
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
