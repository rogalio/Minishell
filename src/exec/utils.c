/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:17:24 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 22:38:24 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_last_command(int i, int command_count)
{
	return (i == command_count - 1);
}

int	check_pid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

void	handle_command_not_found(t_command *command, t_minishell *minishell, char **split)
{
	if (command->heredoc && !(command->args[0]))
	{
		free_resources(minishell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		if (split)
			ft_putstr_fd(split[0], STDERR_FILENO);
		else
			ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free_resources(minishell);
		exit(NOTFND_ERR);
	}
}

void	cleanup_and_exit(t_command *command, t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
		perror(command->args[0]);
	if (g_exit_signal)
	{
		status = g_exit_signal;
		g_exit_signal = 0;
	}
	free_resources(minishell);
	exit(status);
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
	}
	//print msg erreur
	exit_stat = WEXITSTATUS(childval);
	if (g_exit_signal)
		g_exit_signal = 0;
	return (exit_stat);
}
