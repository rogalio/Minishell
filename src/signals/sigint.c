/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:08:14 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 22:41:03 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/*
Le code 130 est conventionnellement utilisé pour indiquer une
sortie forcée due à un signal SIGINT
*/
void	sigint_handler(int signum)
{
	(void)signum;
	g_exit_signal = SIGINT_ERR;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_process_handler(int signum)
{
	(void)signum;
	g_exit_signal = SIGINT_ERR;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigint_heredoc_handler(int signum)
{
	(void)signum;
	close(0);
	g_exit_signal = SIGINT_ERR;
	write(STDOUT_FILENO, "\n", 1);
}
