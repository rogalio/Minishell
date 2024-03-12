/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:36:54 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/11 15:34:49 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

void	init_signals(void);
void	init_process_signals(void);

#endif