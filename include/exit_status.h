/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 18:22:16 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# include "minishell.h"

/* exit_status.c */
int	exit_process(t_minishell *minishell);
int	exit_all(t_minishell *minishell);

/* get_exit_status.c */
int	get_exit_status(t_pipeline *pipeline, t_minishell *minishell);

#endif