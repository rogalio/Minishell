/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:34 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/06 17:13:04 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

typedef struct s_pipe
{
    int pipe_prev[0];
    int pipe_next[1];
} t_pipe;

void swap_pipe_fd(t_pipe *pipe)
{
    close(pipe->pipe_prev[0]);
    close(pipe->pipe_prev[1]);
    pipe->pipe_prev[0] = pipe->pipe_next[0];
    pipe->pipe_prev[1] = pipe->pipe_next[1];
    pipe->pipe_next[0] = -1;
    pipe->pipe_next[1] = -1;
}

void close_pipe_fd(t_pipe *pipe)
{
    close(pipe->pipe_prev[0]);
    close(pipe->pipe_prev[1]);
    close(pipe->pipe_next[0]);
    close(pipe->pipe_next[1]);
}

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

bool check_if_builtins(char *cmd, char ** args, t_data *data)
{
    t_builtins builtins[] = {
        {"echo", echo},
        {"cd", cd},
        {"pwd", pwd},
        {"unset", unset},
        {"exit", exit_shell},
        {NULL, NULL}
    };
    int i;

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

void	execute_command(t_command *command, t_data *data)
{
    char	**args;
    char	*path;

    args = command->args;
    if (check_if_builtins(args[0],args, data))
        return ;
    path = find_path(args[0]);
    if (!path)
    {
        printf("minishell: %s: command not found\n", args[0]);
        exit(EXIT_FAILURE);
    }
    execve(path, args, env_to_char_array(data->env));
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
int create_pipe(t_pipe *pipen)
{
    if (pipe(pipen->pipe_next) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    return (0);
}

// Fonction pour initialiser un processus enfant
void init_child_process(t_command *command, t_pipe *pipe_fds, int in_fd, t_data *data)
{
    redirect_if_needed(command);
    if (in_fd != 0)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (pipe_fds->pipe_next[1] != -1)
    {
        dup2(pipe_fds->pipe_next[1], STDOUT_FILENO);
        close(pipe_fds->pipe_next[1]);
    }
    execute_command(command, data);
}

// Fonction pour gérer un processus parent |
void handle_parent_process(t_pipe *pipe_fds, int *in_fd)
{
    close_pipe_fd(pipe_fds);
    swap_pipe_fd(pipe_fds);
    *in_fd = pipe_fds->pipe_prev[0];

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


bool check_if_builtins_cd_or_unset(char *cmd, char ** args, t_data *data)
{
    t_builtins builtins[] = {

        {"cd", cd},
        {"unset", unset},
        {NULL, NULL}
    };
    int i;

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

bool check_if_builtins_others(char *cmd, char ** args, t_data *data)
{
    t_builtins builtins[] = {
        {"echo", echo},
        {"pwd", pwd},
        {"exit", exit_shell},
        {NULL, NULL}
    };
    int i;

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


void	execute_pipeline(t_pipeline *pipeline, char **envp)
{
    t_pipe pipe_fds;
    int		in_fd;
    int		i;
    pid_t	pid;
    t_env    *env;
    t_data   data; // Initialisation de t_data

    env = init_env(envp);
    data.env = env; // Assignation de t_env à data.env
    in_fd = 0;
    i = 0;
   //if (check_if_builtins_cd_or_unset(pipeline->commands[i]->args[0], pipeline->commands[i]->args, &data))
    //        i++;
    while (i < pipeline->command_count)
    {
        if (i < pipeline->command_count - 1)
            create_pipe(&pipe_fds);
        pid = fork();
        check_pid_error(pid);
        if (is_child_process(pid))
            init_child_process(pipeline->commands[i], &pipe_fds, in_fd, &data);
        else
            handle_parent_process(&pipe_fds, &in_fd);
        i++;
    }
    wait_for_children_to_finish(pipeline->command_count);
}


