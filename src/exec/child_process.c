/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:46:26 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 22:39:18 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	execute_split_cmd(t_command *command, t_data *data, \
t_minishell *minishell)
{
	char	*path;
	char	**envp;
	char	**split;

	path = NULL;
	envp = NULL;
	split = ft_split2(command->args[0], ' ');
	if (!split)
		cleanup_and_exit(command, minishell, UNEXPEC_ERR);
	path = find_path(split[0], minishell);
	if (!path)
		handle_command_not_found(command, minishell, split);
	envp = env_to_char_array(data->env);
	execve(path, split, envp);
	free_tab(split);
	cleanup_and_exit(command, minishell, EXIT_FAILURE);
}

static void	execute_regular_cmd(t_command *command, t_data *data, \
t_minishell *minishell)
{
	char	**envp;
	char	*path;

	envp = NULL;
	path = find_path(command->args[0], minishell);
	if (!path)
		handle_command_not_found(command, minishell, NULL);
	envp = env_to_char_array(data->env);
	execve(path, command->args, envp);
	cleanup_and_exit(command, minishell, EXIT_FAILURE);
}

static bool	check_command_args(t_command *command)
{
	int	i;

	i = -1;
	while (command->args[0][++i])
	{
		if (command->args[0][i] == ' ')
			return (true);
	}
	return (false);
}

static void	execute_cmd(t_command *command, t_data *data, \
t_minishell *minishell)
{
	if (redirect_if_needed(command))
		cleanup_and_exit(command, minishell, EXIT_FAILURE);
	if (is_builtins(command->args[0]))
	{
		execute_builtin(command->args[0], command->args, data, minishell);
		cleanup_and_exit(command, minishell, minishell->exit_status);
	}
	else
	{
		if (check_command_args(command))
			execute_split_cmd(command, data, minishell);
		else
			execute_regular_cmd(command, data, minishell);
	}
}

void	handle_child_process(int in_fd, int pipe_fds[2], int i, \
t_minishell *minishell)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (!is_last_command(i, minishell->pipeline->command_count))
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	execute_cmd(minishell->pipeline->commands[i], minishell->data, minishell);
	exit(EXIT_FAILURE);
}
