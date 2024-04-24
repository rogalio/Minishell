/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:21:17 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/24 17:38:36 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

// int	g_exit_signal = 0;

/*
Le code 130 est conventionnellement utilisé pour indiquer une
sortie forcée due à un signal SIGINT
*/
void	sigint_handler(int signum)
{
	(void)signum;
	g_exit_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_process_handler(int signum)
{
	(void)signum;
	g_exit_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigint_heredoc_handler(int signum)
{
	(void)signum;
	close(0);
	g_exit_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigquit_process_handler(int signum)
{
	(void)signum;
	g_exit_signal = 131;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_process_signals(void)
{
	signal(SIGINT, sigint_process_handler);
	signal(SIGQUIT, sigquit_process_handler);
}


void	init_heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
