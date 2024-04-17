// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredocs.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/16 14:15:45 by cabdli            #+#    #+#             */
// /*   Updated: 2024/04/17 15:46:12 by cabdli           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "heredocs.h"

// char	*get_heredoc_name(int i)
// {
// 	return (ft_strjoin(".tmp_heredoc", ft_itoa(i)));
// }

// int	open_heredoc(t_heredoc *heredoc, int i)
// {
// 	int	pid;
// 	int	childval;

// 	heredoc->heredoc_name[i] = get_hredoc_name(i);
// 	if (!heredoc->heredoc_name[i])
// 		return (0);
// }

// int	handle_cmd_heredoc(t_heredoc *heredoc)
// {
// 	int	i;

// 	i = -1;
// 	if (!heredoc)
// 		return (1);
// 	while (++i < heredoc->nb_heredocs)
// 	{
// 		if (!open_heredoc(heredoc, i))
// 			return (0);
// 	}
// }

// int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < pipeline->command_count)
// 	{
// 		if (!handle_cmd_heredoc(pipeline->commands[i]->heredoc))
// 			return (0);
// 	}
// 	return (1);
// }
