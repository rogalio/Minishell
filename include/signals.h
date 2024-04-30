/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:36:54 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/30 18:52:58 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

/* init_signals.c */
void	init_signals(void);
void	init_process_signals(void);
void	init_heredoc_signals(void);

/* sigquit.c */
void	sigquit_process_handler(int signum);

/* sigint.c */
void	sigint_handler(int signum);
void	sigint_process_handler(int signum);
void	sigint_heredoc_handler(int signum);

#endif