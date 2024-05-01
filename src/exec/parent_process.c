/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:52:34 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/01 14:52:51 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_parent_process(int *in_fd, int pipe_fds[2], int i, \
t_pipeline *pipeline)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (i < pipeline->command_count - 1)
	{
		*in_fd = pipe_fds[0];
		close(pipe_fds[1]);
	}
}
