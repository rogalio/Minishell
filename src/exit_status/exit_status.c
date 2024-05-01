/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:07 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/01 16:05:22 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "builtins.h"

int	exit_process(t_minishell *minishell)
{
	int	exit_status;

	exit_status = minishell->exit_status;
	if (exit_status == UNEXPEC_ERR)
	{
		minishell->error = MALLOC;
		print_err_msg(&(minishell->error));
	}
	if (g_exit_signal)
	{
		exit_status = g_exit_signal;
		g_exit_signal = 0;
	}
	free_resources(minishell);
	exit(exit_status);
}

int	exit_all(t_minishell *minishell)
{
	int	exit_status;

	exit_status = minishell->exit_status;
	free_minishell(&minishell);
	return (exit_status);
}
