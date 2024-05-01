/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 16:11:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
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

	i = 0;
	in_fd = 0;
	(void)data;
	while (i < pipeline->command_count)
	{
		if (!is_last_command(i, pipeline->command_count))
			create_pipe(pipe_fds);
		pid = fork();
		check_pid_error(pid);
		if (pid == 0)
			handle_child_process(in_fd, pipe_fds, i, minishell);
		else
			handle_parent_process(&in_fd, pipe_fds, i, pipeline);
		i++;
	}
	wait_for_children_to_finish(pipeline->command_count);
	return (0);
}

static void	restore_standard_descriptors(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

static int	execute_single_builtin(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (redirect_if_needed(pipeline->commands[0]))
		return (1);
	printf("TEST\n");
	execute_builtin(pipeline->commands[0]->args[0], \
	pipeline->commands[0]->args, data, minishell);
	restore_standard_descriptors(saved_stdout, saved_stdin);
	return (0);
}

void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	(*execute)(t_pipeline *, t_data *, t_minishell *);
	int	cmd_count;

	cmd_count = pipeline->command_count;
	if (cmd_count == 1 && is_builtins(pipeline->commands[0]->args[0]))
		execute = execute_single_builtin;
	else
		execute = execute_commands;
	if (execute(pipeline, data, minishell))
		return ;
}
