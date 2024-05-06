/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:17:24 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 15:02:59 by cabdli           ###   ########.fr       */
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

void	handle_command_not_found(t_command *command, t_minishell *minishell, \
char **split)
{
	if ((command->heredoc || command->redirect_out) && !(command->args[0]))
	{
		free_resources(minishell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (split)
		{
			ft_putstr_fd(split[0], STDERR_FILENO);
			free_tab(split);
		}
		else
			ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_resources(minishell);
		exit(NOTFND_ERR);
	}
}

void	cleanup_and_exit(t_command *command, t_minishell *minishell, \
int status, int perr)
{
	if (perr == 1)
		perror(command->args[0]);
	if (g_exit_signal)
	{
		status = g_exit_signal;
		g_exit_signal = 0;
	}
	free_resources(minishell);
	exit(status);
}
