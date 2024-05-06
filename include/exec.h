/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:58 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/06 15:03:17 by cabdli           ###   ########.fr       */
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
void	restore_standard_descriptors(int saved_stdout, int saved_stdin);

/* redirections.c */
int		redirect_if_needed(t_command *command);

/* builtins.c */
bool	is_builtins(char *cmd);
int		execute_builtin(char *cmd, char **args, t_data *data, \
t_minishell *minishell);

/* find_paths.c */
char	*find_path(const char *cmd, t_minishell *minishell);

/* child_process.c */
void	handle_child_process(int in_fd, int pipe_fds[2], int i, \
t_minishell *minishell);

/* parent_process.c */
void	handle_parent_process(int *in_fd, int pipe_fds[2], int i, \
t_pipeline *pipeline);
int		wait_for_children_to_finish(int command_count, t_pipeline *pipeline);

/* utils.c */
bool	is_last_command(int i, int command_count);
int		check_pid_error(pid_t pid);
void	handle_command_not_found(t_command *command, \
t_minishell *minishell, char **split);
void	cleanup_and_exit(t_command *command, t_minishell *minishell, \
int status, int perr);

/* utils2.c */
void	free_tab(char **tab);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
char	**env_to_char_array(t_env *env);
char	**ft_split2(char const *s, char c);

#endif