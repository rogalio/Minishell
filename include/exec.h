/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:58 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/11 18:47:00 by rogalio          ###   ########.fr       */
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

void	execute_pipeline(t_pipeline *pipeline, t_data *data, t_minishell *minishell);

#endif