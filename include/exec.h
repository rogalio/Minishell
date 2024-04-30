/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:58 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/30 18:30:20 by cabdli           ###   ########.fr       */
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

typedef struct s_pipe
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
}t_pipe;

/* exec.c */
void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell);

/* redirections.c */
int		redirect_heredeocs(t_command *command);
int		redirect_in(t_command *command);
int		redirect_out(t_command *command);
int		redirect_if_needed(t_command *command);

#endif