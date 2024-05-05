/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/05 22:16:49 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "prompt.h"
#include "exit_status.h"

int	g_exit_signal;

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(envp);
	if (!data->env)
		return (free(data), NULL);
	return (data);
}

static t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	minishell->data = init_data(envp);
	if (!minishell->data)
		return (free(minishell), NULL);
	return (minishell);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argv;
	minishell = NULL;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2), UNEXPEC_ERR);
	minishell = init_minishell(envp);
	if (!minishell)
		return (perror("minishell"), UNEXPEC_ERR);
	run_shell(minishell);
	return (exit_all(minishell));
}
