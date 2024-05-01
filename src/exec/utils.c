/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:17:24 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/01 13:36:01 by cabdli           ###   ########.fr       */
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

void	handle_command_not_found(t_command *command, t_minishell *minishell)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(command->args[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_resources(minishell);
	exit(EXIT_FAILURE);
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

void	cleanup_and_exit(t_command *command, t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
		perror(command->args[0]);
	free_resources(minishell);
	exit(status);
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

// void	swap_pipe(t_pipe *pipe1, t_pipe *pipe2)
// {
// 	t_pipe	tmp;

// 	tmp = *pipe1;
// 	*pipe1 = *pipe2;
// 	*pipe2 = tmp;
// }


// void	free_token_test(t_token *token)
// {
// 	if (!token)
// 		return ;
// 	free(token->value);
// 	free(token);
// }
