/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:21:17 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/19 13:45:26 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

//Le code 130 est conventionnellement utilisé pour indiquer une
//sortie forcée due à un signal SIGINT
void	sigint_handler(int signum)
{
	(void)signum;
	//g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_process_handler(int signum)
{
	(void)signum;
	//g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigquit_process_handler(int signum)
{
	(void)signum;
	//g_exit_status = 131;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	init_process_signals(void)
{
	signal(SIGINT, sigint_process_handler);
	signal(SIGQUIT, sigquit_process_handler);
}
