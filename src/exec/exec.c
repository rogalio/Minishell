/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 13:47:47 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**ft_split2(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = ft_calloc((ft_strlen(s) + 1), sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > k)
		{
			tab[j] = ft_calloc((i - k + 1), sizeof(char));
			if (!tab[j])
				return (0);
			ft_strlcpy(tab[j], s + k, i - k + 1);
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}









void	wait_for_children_to_finish(int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		wait(NULL);
		i++;
	}
}




// handle parent process
void	handle_parent_process(int *in_fd, int pipe_fds[2], int i, \
t_pipeline *pipeline)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (i < pipeline->command_count - 1)
	{
		*in_fd = pipe_fds[0];
		close(pipe_fds[1]);
	}
}

int	execute_commands(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int		i;
	pid_t	pid;
	int		in_fd;
	int		pipe_fds[2];

	i = 0;
	in_fd = 0;
	(void)data;
	while (i < pipeline->command_count)
	{
		if (!is_last_command(i, pipeline->command_count))
			create_pipe(pipe_fds);
		pid = fork();
		check_pid_error(pid);
		if (pid == 0)
			handle_child_process(in_fd, pipe_fds, i, minishell);
		else
			handle_parent_process(&in_fd, pipe_fds, i, pipeline);
		i++;
	}
	wait_for_children_to_finish(pipeline->command_count);
}

int	execute_single_builtin(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!redirect_if_needed(pipeline->commands[0]))
		return (1);
	execute_builtin(pipeline->commands[0]->args[0], \
	pipeline->commands[0]->args, data, minishell);
	restore_standard_descriptors(saved_stdout, saved_stdin);
}

void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	(*execute)(t_pipeline *, t_data *, t_minishell *);
	int	cmd_count;

	cmd_count = pipeline->command_count;
	if (cmd_count == 1 && is_builtins(pipeline->commands[0]->args[0]))
		execute = execute_single_builtin;
	else
		execute = execute_commands;
	if (execute(pipeline, data, minishell))
		return ;
}

