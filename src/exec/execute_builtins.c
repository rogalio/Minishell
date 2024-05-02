/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:49:34 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 13:31:19 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// {"env", env},
bool	is_builtins(char *cmd)
{
	int					i;
	static t_builtins	builtins[] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"unset", unset},
	{"exit", exit_shell},
	{"export", export},
	{NULL, NULL}};

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
	int					i;
	static t_builtins	builtins[] = {
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
			minishell->exit_status = builtins[i].func(data, minishell);
			return (true);
		}
		i++;
	}
	return (false);
}
