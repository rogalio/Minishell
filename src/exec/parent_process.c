/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:52:34 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 16:02:43 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_parent_process(int *in_fd, int pipe_fds[2], int i, \
t_pipeline *pipeline)
{
	signal(SIGINT, SIG_IGN);
	if (*in_fd != 0)
		close(*in_fd);
	if (i < pipeline->command_count - 1)
	{
		*in_fd = pipe_fds[0];
		close(pipe_fds[1]);
	}
}

int	wait_for_children_to_finish(int command_count, t_pipeline *pipeline)
{
	int	childval;
	int	exit_stat;
	int	i;

	childval = 0;
	exit_stat = 0;
	i = -1;
	while (++i < command_count)
	{
		if (waitpid(pipeline->commands[i]->pid, &childval, 0) == -1)
			return (perror("minishell"), 1);
		if (WIFSIGNALED(childval))
		{
			exit_stat = WTERMSIG(childval);
			if (exit_stat == SIGTERM)
				write(STDOUT_FILENO, "\n", 1);
			else if (exit_stat == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
			else if (exit_stat == SIGQUIT)
				write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		}
	}
	if (WIFSIGNALED(childval))
	{
		exit_stat = WTERMSIG(childval);
		return (exit_stat + 128);
	}
	else if (WIFEXITED(childval))
		exit_stat = WEXITSTATUS(childval);
	return (exit_stat);
}
