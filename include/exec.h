/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:58 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/30 19:31:24 by cabdli           ###   ########.fr       */
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
# include "minishell.h"
# include "pipeline.h"
# include "builtins.h"
# include "heredocs.h"
# include "signals.h"
# include "token.h"

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

/* builtins.c */
bool	is_builtins(char *cmd);
bool	execute_builtin(char *cmd, char **args, t_data *data, \
t_minishell *minishell);

/* utils.c */
void	restore_standard_descriptors(int saved_stdout, int saved_stdin);
bool	is_last_command(int i, int command_count);
int		create_pipe(int pipe_fds[2]);
void	check_pid_error(pid_t pid);
void	cleanup_and_exit(t_command *command, t_minishell *minishell, \
int status);
void	free_tab(char **tab);
bool	check_command_args(t_command *command);
static char	*search_in_current(const char *cmd);
static char	**get_search_paths(t_env *env);
static char	*check_directories(char **dirs, const char *cmd);

#endif