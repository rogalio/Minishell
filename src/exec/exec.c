/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/19 13:47:59 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "signals.h"

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
	tab = malloc(sizeof(char *) * (ft_strlen(s) + 1));
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
			tab[j] = malloc(sizeof(char) * (i - k + 1));
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
	envp = malloc(sizeof(char *) * (i + 1));
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

void	execute_command(t_command *command, t_data *data)
{
	char	**envp;
	char	*path;

	// Gestion des redirections spécifiques à la commande
	redirect_if_needed(command);
	// Exécution de la commande externe ou intégrée
	if (!check_if_builtins(command->args[0], command->args, data))
	{
		path = find_path(command->args[0]);
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
	exit(EXIT_SUCCESS); // Sortie du processus enfant après exécution de la commande intégrée
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

// Fonction pour initialiser un processus enfant
void	init_child_process(t_command *command, int pipe_fds[2], int in_fd, t_data *data)
{
	char	*path;
	char	**envp;

	// Si nous avons un fd d'entrée autre que stdin, dupliquez-le sur stdin et fermez-le
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	// Pour le pipe, dupliquez l'extrémité d'écriture sur stdout si nécessaire
	if (pipe_fds[1] != STDOUT_FILENO) {
		dup2(pipe_fds[1], STDOUT_FILENO);
	}
	close(pipe_fds[0]);
	// Toujours fermer l'extrémité de lecture dans le processus enfant
	// Gestion des redirections spécifiques à la commande
	redirect_if_needed(command);
	// Exécution de la commande externe ou intégrée
	if (!check_if_builtins(command->args[0], command->args, data))
	{
		path = find_path(command->args[0]);
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
	exit(EXIT_SUCCESS); // Sortie du processus enfant après exécution de la commande intégrée
}

/* 
Fonction pour gérer un processus parent |
- close(pipe_fds[1]);
==> Toujours fermer l'extrémité d'écriture du pipe dans le parent
- close(*in_fd);
==> Fermer le précédent descripteur d'entrée si ce n'est pas STDIN
- *in_fd = pipe_fds[0];
==> Préparer l'extrémité de lecture pour le prochain enfant
*/
void	handle_parent_process(int pipe_fds[2], int *in_fd)
{
	close(pipe_fds[1]);
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = pipe_fds[0];
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

void	execute_pipeline(t_pipeline *pipeline, t_data *data)
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
	int		i;
	//int prev_fd = -1; // Stocke l'fd de sortie du pipe précédent

	in_fd = 0;
	i = -1;
	init_process_signals();
	if (ft_strcmp(pipeline->commands[0]->args[0], "cd") == 0 || \
	ft_strcmp(pipeline->commands[0]->args[0], "unset") == 0)
	{
		check_if_builtins_cd_or_unset(pipeline->commands[0]->args[0], \
		pipeline->commands[0]->args, data);
		return ;
	}
	while (++i < pipeline->command_count)
	{
		if (i < pipeline->command_count - 1)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // Enfant
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
			execute_command(pipeline->commands[i], data);
			exit(EXIT_SUCCESS);
		}
		else // Parent
		{
			wait(NULL); // Attend le processus enfant pour s'assurer que la sortie est prête pour la commande suivante
			if (in_fd != 0)
				close(in_fd);
			if (i < pipeline->command_count - 1)
			{
				in_fd = pipe_fds[0];
				close(pipe_fds[1]);
			}
		}
	}
}
