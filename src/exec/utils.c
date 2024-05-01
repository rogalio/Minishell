/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:17:24 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/01 15:16:56 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_last_command(int i, int command_count)
{
	return (i == command_count - 1);
}

void	check_pid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	handle_command_not_found(t_command *command, t_minishell *minishell)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(command->args[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_resources(minishell);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_command *command, t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
		perror(command->args[0]);
	free_resources(minishell);
	exit(status);
}

void	wait_for_children_to_finish(int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		wait(NULL);
		i++;
	}
}
