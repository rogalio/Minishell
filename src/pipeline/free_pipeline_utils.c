/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:10:25 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/17 19:21:23 by cabdli           ###   ########.fr       */
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
	if (heredoc->delimiter)
		free(heredoc->delimiter);
	if (heredoc->hdoc_name)
		free(heredoc->hdoc_name);
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
