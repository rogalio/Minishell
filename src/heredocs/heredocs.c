/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/16 16:08:44 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredocs.h"

int	open_heredoc(t_heredoc *heredoc, int i)
{
	int	pid;
	int	childval;

	heredoc->heredoc_name[i] = ;
}

int	handle_cmd_heredoc(t_heredoc *heredoc)
{
	int	i;

	i = -1;
	if (!heredoc)
		return (1);
	while (++i < heredoc->nb_heredocs)
		open_heredoc(heredoc, i);
}

int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell)
{
	int	i;

	i = -1;
	while (++i < pipeline->command_count)
	{
		handle_cmd_heredoc(pipeline->commands[i]->heredoc);
	}
}
