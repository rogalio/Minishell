/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:58 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/16 14:39:16 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "pipeline.h"
# include "builtins.h"
# include "minishell.h"
# include "heredocs.h"

void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell);

#endif