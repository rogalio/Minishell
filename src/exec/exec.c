/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/09 16:23:47 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "signals.h"
#include "token.h"

typedef struct s_pipe
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
}t_pipe;

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

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split2(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(paths);
	return (NULL);
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

bool	check_if_builtins_cd_or_unset(char *cmd, char **args, t_data *data)
{
	t_builtins	builtins[] =
	{
		// {"echo", echo},
		{"cd", cd},
		//{"pwd", pwd},
		{"unset", unset},
		//{"exit", exit_shell},
		{NULL, NULL}
	};
	int			i;

	i = 0;
	data->args = args;
	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, cmd) == 0)
		{
			builtins[i].func(data);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_if_builtins(char *cmd, char **args, t_data *data)
{
	t_builtins	builtins[] = {
		{"echo", echo},
		{"cd", cd},
		{"pwd", pwd},
		{"unset", unset},
		{"exit", exit_shell},
		{NULL, NULL}
	};
	int			i;

	i = 0;
	data->args = args;
	while (builtins[i].name)
	{
		if (strcmp(builtins[i].name, cmd) == 0)
		{
			builtins[i].func(data);
			return (true);
		}
		i++;
	}
	return (false);
}

void	redirect_if_needed(t_command *command)
{
	int	fd_in;
	int	fd_out;

	// Gestion de la redirection d'entrée
	if (command->redirect_in)
	{
		fd_in = open(command->redirect_in->file, O_RDONLY);
		if (fd_in == -1)
		{
			perror("open input file");
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	// Gestion de la redirection de sortie
	if (command->redirect_out)
	{
		fd_out = open(command->redirect_out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (command->heredoc)
	{

	}
}

void free_token_test(t_token *token)
{
		if (!token)
		return ;
	free(token->value);
	free(token);
}


void	execute_command(t_command *command, t_data *data, t_minishell *minishell)
{
	char	**envp;
	char	*path;
	(void)minishell;


	// Gestion des redirections spécifiques à la commande
	redirect_if_needed(command);
	// Exécution de la commande externe ou intégrée
	if (!check_if_builtins(command->args[0], command->args, data))
	{
		path = find_path(command->args[0]);
		printf("path = %s\n", path);
		if (path)
		{
			envp = env_to_char_array(data->env);
			execve(path, command->args, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "minishell: %s: command not found\n", command->args[0]);
			exit(EXIT_FAILURE);
		}
	}
	// add free
	free_token_list(&minishell->token_list);
	free_pipeline(minishell->pipeline);
	free_minishell(&minishell);
	exit(EXIT_SUCCESS);
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
void handle_child_process(int in_fd, int pipe_fds[2], int i, t_pipeline *pipeline, t_data *data, t_minishell *minishell)
{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < pipeline->command_count - 1)
			{
				close(pipe_fds[0]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			execute_command(pipeline->commands[i], data, minishell);
			exit(EXIT_SUCCESS);
		}

// handle parent process
void handle_parent_process(int *in_fd, int pipe_fds[2], int i, t_pipeline *pipeline, t_minishell *minishell)
{
		(void)minishell;
    if (*in_fd != 0)
        close(*in_fd);
    if (i < pipeline->command_count - 1)
		{
        *in_fd = pipe_fds[0];
        close(pipe_fds[1]);
    }
}

void	execute_pipeline(t_pipeline *pipeline, t_data *data, t_minishell *minishell)
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
	int		i;

	in_fd = 0;
	i = 0;
	init_process_signals();

	if (ft_strcmp(pipeline->commands[0]->args[0], "cd") == 0 || ft_strcmp(pipeline->commands[0]->args[0], "unset") == 0 || ft_strcmp(pipeline->commands[0]->args[0], "export") == 0)
	{
		check_if_builtins_cd_or_unset(pipeline->commands[0]->args[0], pipeline->commands[0]->args, data);
		return ;
	}
	printf("command count666 %d\n", pipeline->command_count);
	while (i < pipeline->command_count)
	{
		if (!is_last_command(i, pipeline->command_count))
			create_pipe(pipe_fds);
		pid = fork();
		check_pid_error(pid);
		if (is_child_process(pid))
			handle_child_process(in_fd, pipe_fds, i, pipeline, data, minishell);
		else
			handle_parent_process(&in_fd, pipe_fds, i, pipeline, minishell);
		i++;
	}
	wait_for_children_to_finish(pipeline->command_count);
}
