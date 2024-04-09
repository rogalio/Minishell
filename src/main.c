/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/09 15:21:05 by rogalio          ###   ########.fr       */
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



static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(envp);
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
		return (NULL);
	return (minishell);
}

/*

void	free_env2(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void free_data(t_data *data)
{
	if (!data)
		return ;
	free_env2(data->env);
	free(data->args);
	free(data);
}

void free_minishell(t_minishell *minishell)
{
	free_data(minishell->data);
	free(minishell);
}
*/

void free_env2(t_env **env)
{
    t_env *current;
    t_env *next;

    if (!env || !*env)
        return;

    current = *env;
    while (current != NULL)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    *env = NULL;
}

void free_data(t_data **data)
{
    if (!data || !*data)
        return;

    free_env2(&(*data)->env);
    free(*data);
    *data = NULL;
}

void free_minishell(t_minishell **minishell)
{
    if (!minishell || !*minishell)
        return;

    free_data(&(*minishell)->data);
    free(*minishell);
    *minishell = NULL;
}









int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argv;
	minishell = NULL;
	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26), 1);
	minishell = init_minishell(envp);
	if (!minishell)
		return (/*free_all(),*/1);
	run_shell(minishell);
	free_minishell(&minishell);
	return (0);
}
