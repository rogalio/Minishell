/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:21:17 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/26 15:09:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

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
