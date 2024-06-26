/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:06:04 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 15:20:45 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigquit_process_handler(int signum)
{
	(void)signum;
	g_exit_signal = SIGQUIT_ERR;
	rl_on_new_line();
	rl_redisplay();
}

// void	sigquit_process_handler(int signum)
// {
// 	(void)signum;
// 	g_exit_signal = SIGQUIT_ERR;
// 	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
// }
