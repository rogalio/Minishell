/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/30 18:30:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "signals.h"
#include "token.h"

void	swap_pipe(t_pipe *pipe1, t_pipe *pipe2)
{
	t_pipe	tmp;

	tmp = *pipe1;
	*pipe1 = *pipe2;
	*pipe2 = tmp;
}

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

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	total_length;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + ft_strlen(s2) + ft_strlen(s3);
	new_str = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcat(new_str, s2, s1_len + s2_len + 1);
	ft_strlcat(new_str, s3, total_length + 1);
	return (new_str);
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

static char	*search_in_current(const char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*find_path(const char *cmd, t_minishell *minishell)
{
	char	**paths;
	char	*found_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 || \
	strncmp(cmd, "../", 3) == 0)
		return (search_in_current(cmd));
	paths = get_search_paths(minishell->data->env);
	if (!paths)
		return (free(paths), NULL);
	found_path = check_directories(paths, cmd);
	free_tab(paths);
	return (found_path);
}

char	**env_to_char_array(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}


// {"env", env},
bool	is_builtins(char *cmd)
{
	int			i;
	t_builtins	builtins[] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"unset", unset},
	{"exit", exit_shell},
	{"export", export},
	{NULL, NULL}
	};

	i = 0;
	if (!cmd)
		return (false);
	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, cmd) == 0)
			return (true);
		i++;
	}
	return (false);
}

//{"env", env},
bool	execute_builtin(char *cmd, char **args, t_data *data, \
t_minishell *minishell)
{
	int			i;
	t_builtins	builtins[] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"unset", unset},
	{"exit", exit_shell},
	{"export", export},
	{NULL, NULL}
	};

	i = 0;
	if (cmd == NULL)
		return (false);
	data->args = args;
	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, cmd) == 0)
		{
			builtins[i].func(data, minishell);
			return (true);
		}
		i++;
	}
	return (false);
}

void	free_token_test(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}


void	free_resources2(t_minishell *minishell)
{
	free_token_list(&minishell->token_list);
	free_pipeline(&minishell->pipeline);
	free_minishell(&minishell);
}

void	handle_command_not_found(t_command *command, t_minishell *minishell)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(command->args[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_resources2(minishell);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_command *command, t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
		perror(command->args[0]);
	free_resources2(minishell);
	exit(status);
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

void	execute_split_cmd(t_command *command, t_data *data, \
t_minishell *minishell)
{
	int		i;
	char	*path;
	char	**envp;
	char	**split;

	i = 0;
	path = NULL;
	envp = NULL;
	split = ft_split2(command->args[0], ' ');
	if (!split)
		//gerer erreur
	path = find_path(split[0], minishell);
	if (!path && command->heredoc)
	{
		free_resources2(minishell);
		exit(EXIT_SUCCESS);
	}
	if (!path)
		handle_command_not_found(command, minishell);
	envp = env_to_char_array(data->env);
	execve(path, split, envp);
	free_tab(split);
	cleanup_and_exit(command, minishell, EXIT_FAILURE);
}

void	execute_regular_cmd(t_command *command, t_data *data, t_minishell *minishell)
{
	char	**envp;
	char	*path;

	envp = NULL;
	path = find_path(command->args[0], minishell);
	if (!path && command->heredoc)
	{
		free_resources2(minishell);
		exit(EXIT_SUCCESS);
	}
	if (!path)
		handle_command_not_found(command, minishell);
	envp = env_to_char_array(data->env);
	execve(path, command->args, envp);
	cleanup_and_exit(command, minishell, EXIT_FAILURE);
}

void	execute_cmd(t_command *command, t_data *data, t_minishell *minishell)
{
	if (!redirect_if_needed(command))
		cleanup_and_exit(command, minishell, EXIT_FAILURE);
	if (is_builtins(command->args[0]))
	{
		execute_builtin(command->args[0], command->args, data, minishell);
		cleanup_and_exit(command, minishell, EXIT_SUCCESS);
	}
	else
	{
		if (check_command_args(command))
			execute_split_cmd(command, data, minishell);
		else
			execute_regular_cmd(command, data, minishell);
	}
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

// fonction check if pid = -1
void	check_pid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

// function to check if pid is 0
bool	is_child_process(pid_t pid)
{
	return (pid == 0);
}

// function to check_is_last_command
bool	is_last_command(int i, int command_count)
{
	return (i == command_count - 1);
}

// Fonction pour créer un pipe et gérer les erreurs
int	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

// handle child process
void	handle_child_process(int in_fd, int pipe_fds[2], int i, \
t_minishell *minishell)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (i < minishell->pipeline->command_count - 1)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	execute_cmd(minishell->pipeline->commands[i], minishell->data, minishell);
	exit(EXIT_SUCCESS);
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

int get_cmd_count(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (pipeline->commands[i])
		i++;
	return (i);
}

// Gère l'exécution de plusieurs commandes avec un pipeline
void	execute_commands(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int		i;
	pid_t	pid;
	int		in_fd;
	int		pipe_fds[2];

	i = 0;
	in_fd = 0;
	while (i < pipeline->command_count)
	{
		if (!is_last_command(i, pipeline->command_count))
			create_pipe(pipe_fds);
		pid = fork();
		check_pid_error(pid);
		if (is_child_process(pid))
			handle_child_process(in_fd, pipe_fds, i, minishell);
		else
			handle_parent_process(&in_fd, pipe_fds, i, pipeline);
		i++;
	}
	wait_for_children_to_finish(pipeline->command_count);
}



void	restore_standard_descriptors(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	execute_single_builtin(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!redirect_if_needed(pipeline->commands[0]))
		/*gerer erreur*/;
	if (is_builtins(pipeline->commands[0]->args[0]))
		execute_builtin(pipeline->commands[0]->args[0], \
		pipeline->commands[0]->args, data, minishell);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);

}

void	execute_pipeline(t_pipeline *pipeline, t_data *data, \
t_minishell *minishell)
{
	void	(*execute)(t_pipeline *, t_data *, t_minishell *);
	int		cmd_count;

	cmd_count = pipeline->command_count;
	if (cmd_count == 1 && is_builtins(pipeline->commands[0]->args[0]))
		execute = execute_single_builtin;
	else
		execute = execute_commands;
	execute(pipeline, data, minishell);
}

