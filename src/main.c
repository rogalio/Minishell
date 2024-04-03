/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/03 14:23:20 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"
#include "exec.h"
#include "prompt.h"
#include "utils.h"

extern int	g_exit_signal;

void free_data(t_data *data)
{
	free_env(data->env);
	//free(data->args);
	free(data);
}

void free_minishell(t_minishell *minishell)
{
	free_data(minishell->data);
	free(minishell);
}

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
		return (ft_putstr_fd("Error: too many arguments\n", 2), 1);
	minishell = init_minishell(envp);
	if (!minishell)
		return (1);
	run_shell(minishell);
	free_minishell(minishell);
	return (0);
}
