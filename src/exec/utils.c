/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:17:24 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/30 19:31:10 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_standard_descriptors(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

bool	is_last_command(int i, int command_count)
{
	return (i == command_count - 1);
}

int	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	check_pid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	cleanup_and_exit(t_command *command, t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
		perror(command->args[0]);
	free_resources2(minishell);
	exit(status);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

bool	check_command_args(t_command *command)
{
	int	i;

	i = -1;
	while (command->args[0][++i])
	{
		if (command->args[0][i] == ' ')
			return (true);
	}
	return (false);
}

static char	*search_in_current(const char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	**get_search_paths(t_env *env)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
	{
		free(path_env);
		return (NULL);
	}
	paths = ft_split2(path_env, ':');
	free(path_env);
	return (paths);
}

static char	*check_directories(char **dirs, const char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin_three(dirs[i], "/", cmd);
		printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
