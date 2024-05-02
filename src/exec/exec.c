/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/02 18:40:12 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

static int	execute_commands(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int		i;
	pid_t	pid;
	int		in_fd;
	int		pipe_fds[2];

	i = -1;
	in_fd = 0;
	(void)data;
	while (++i < pipeline->command_count)
	{
		if (!is_last_command(i, pipeline->command_count))
		{
			if (create_pipe(pipe_fds))
				return (minishell->exit_status = UNEXPEC_ERR, 1);
		}
		pid = fork();
		pipeline->commands[i]->pid = pid;
		if (check_pid_error(pid))
			return (minishell->exit_status = UNEXPEC_ERR, 1);
		if (pid == 0)
			handle_child_process(in_fd, pipe_fds, i, minishell);
		handle_parent_process(&in_fd, pipe_fds, i, pipeline);
	}
	minishell->exit_status = wait_for_children_to_finish(pipeline->command_count, pipeline);
	return (0);
}

void	restore_standard_descriptors(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

static int	execute_single_builtin(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	minishell->fd_out = dup(STDOUT_FILENO);
	minishell->fd_in = dup(STDIN_FILENO);
	if (redirect_if_needed(pipeline->commands[0]))
		return (minishell->exit_status = UNEXPEC_ERR, 1);
	execute_builtin(pipeline->commands[0]->args[0], \
	pipeline->commands[0]->args, data, minishell);
	restore_standard_descriptors(minishell->fd_out, minishell->fd_in);
	return (0);
}

void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	(*execute)(t_pipeline *, t_data *, t_minishell *);
	int	cmd_count;

	cmd_count = pipeline->command_count;
	init_process_signals();
	if (get_exit_status(pipeline, minishell))
		return ;
	if (cmd_count == 1 && is_builtins(pipeline->commands[0]->args[0]))
		execute = execute_single_builtin;
	else
		execute = execute_commands;
	execute(pipeline, data, minishell);
}
