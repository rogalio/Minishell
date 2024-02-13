/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 15:39:50 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"



char **ft_split2(char const *s, char c)
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

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split2(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute_command(t_command *cmd, char **envp)
{
    char	*path;

    path = find_path(cmd->args[0], envp);
    if (!path)
    {
        perror("Command not found");
        exit(EXIT_FAILURE);
    }
    if (execve(path, cmd->args, envp) == -1)
    {
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
}

void	redirect_if_needed(t_command *cmd)
{
    int	fd;

    if (cmd->redirect_in)
    {
        fd = open(cmd->redirect_in->file, O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening input redirection file");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (cmd->redirect_out)
    {
        fd = open(cmd->redirect_out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Error opening output redirection file");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void	execute_pipeline(t_pipeline *pipeline, char **envp)
{
    int		pipe_fds[2];
    int		in_fd;
    int		i;
    pid_t	pid;

    in_fd = 0;
    i = 0;
    while (i < pipeline->command_count)
    {
        pipe(pipe_fds);
        pid = fork();
        if (pid == 0)
        {
            close(pipe_fds[0]);
            if (i < pipeline->command_count - 1)
                dup2(pipe_fds[1], STDOUT_FILENO);
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            redirect_if_needed(pipeline->commands[i]);
            execute_command(pipeline->commands[i], envp);
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
            close(pipe_fds[1]);
            if (in_fd != 0)
                close(in_fd);
            in_fd = pipe_fds[0];
        }
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    if (in_fd != 0)
        close(in_fd);
}


