/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/22 19:31:28 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"



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

char **env_to_char_array(t_env *env)
{
    int i;
    char **envp;
    t_env *tmp;

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

bool check_if_builtins(char *cmd, char **args, t_env *env)
{
    t_builtins builtins[] = {
        {"echo", echo},
        {"cd", cd},
        {"pwd", pwd},
        {"unset", unset},
        {"exit", exit_shell},
        {NULL, NULL}
    };
    t_data data; // Création d'une instance de t_data
    int i;

    data.env = env; // Ajustez selon la manière dont vous gérez l'environnement
    data.args = args;
    i = 0;
    while (builtins[i].name)
    {
        if (strcmp(builtins[i].name, cmd) == 0)
        {
            builtins[i].func(&data);
            return (true);
        }
        i++;
    }
    return (false);
}

void	execute_command(t_command *command, t_env *env)
{
    char	**args;
    char	*path;
    t_data data;

    data.env = env;
    args = command->args;
    if (check_if_builtins(args[0], args, env))
        return ;
    path = find_path(args[0]);
    if (!path)
    {
        printf("minishell: %s: command not found\n", args[0]);
        exit(EXIT_FAILURE);
    }
    execve(path, args, env_to_char_array(env));
    perror("execve");
    exit(EXIT_FAILURE);
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

// Fonction pour créer un pipe et gérer les erreurs
int create_pipe(int pipe_fds[2])
{
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    return (0);
}

// Fonction pour initialiser un processus enfant
void init_child_process(t_command *command, int pipe_fds[2], int in_fd, t_env *envp)
{
    close(pipe_fds[0]);
    if (in_fd != 0)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    redirect_if_needed(command);
    execute_command(command, envp);
    exit(EXIT_FAILURE);
}

// Fonction pour gérer un processus parent |
void handle_parent_process(int pipe_fds[2], int *in_fd)
{
    close(pipe_fds[1]);
    if (*in_fd != 0)
        close(*in_fd);
    *in_fd = pipe_fds[0];
}


void wait_for_children_to_finish(int command_count)
{
    while (command_count > 0)
    {
        wait(NULL);
        command_count--;
    }
}

// fonction check if pid = -1
void check_pid_error(pid_t pid)
{
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}


// function to check if pid is 0
bool is_child_process(pid_t pid)
{
    return (pid == 0);
}



void	execute_pipeline(t_pipeline *pipeline, char **envp)
{
    int		pipe_fds[2];
    int		in_fd;
    int		i;
    pid_t	pid;
    t_env    *env;


    env = init_env(envp);
    in_fd = 0;
    i = 0;
    while (i < pipeline->command_count)
    {
        create_pipe(pipe_fds);
        pid = fork();
        check_pid_error(pid);
        if (is_child_process(pid))
            init_child_process(pipeline->commands[i], pipe_fds, in_fd, env);
        else
            handle_parent_process(pipe_fds, &in_fd);
        i++;
    }
    wait_for_children_to_finish(pipeline->command_count);
}


