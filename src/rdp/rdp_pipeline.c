/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:48:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/27 16:02:08 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

t_command	**init_commands(int cmd_count)
{
	t_command	**commands;

	commands = ft_calloc((cmd_count + 1), sizeof(t_command *));
	if (!commands)
		return (NULL);
	return (commands);
}

/*
if (!commands[nb_cmd])
		{
			while (nb_cmd > 0)
				free(commands[--nb_cmd]);
			free(commands);
			return (NULL);
		}
==> refactoriser cette partie, faire une seule fonction pour free
en cas d'échec de malloc
*/
int	create_commands(t_pipeline *pipeline, t_token_list *token_list)
{
	int			nb_cmd;

	nb_cmd = -1;
	pipeline->command_count = get_pipe_count(token_list) + 1;
	pipeline->commands = init_commands(pipeline->command_count);
	if (!pipeline->commands)
		return (0);
	while (++nb_cmd < pipeline->command_count)
	{
		pipeline->commands[nb_cmd] = create_cmd();
		if (!pipeline->commands[nb_cmd])
		{
			while (nb_cmd > 0)
				free(pipeline->commands[--nb_cmd]);
			free(pipeline->commands);
			return (0);
		}
	}
	return (1);
}

char	**init_cmds_args(int args_count)
{
	char	**args;

	args = ft_calloc((args_count + 1), sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

int	create_cmds_args(t_pipeline *pipeline, t_token_list *token_list)
{
	int	cmd;

	cmd = -1;
	get_args_count(pipeline, token_list);
	while (++cmd < pipeline->command_count)
	{
		pipeline->commands[cmd]->args = init_cmds_args \
		(pipeline->commands[cmd]->args_count);
		if (!pipeline->commands[cmd]->args)
			return (0);
	}
	return (1);
}

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	//pipeline->commands = NULL;
	//pipeline->command_count = 0;
	return (pipeline);
}

t_pipeline	*create_pipeline(t_token_list *token_list)
{
	t_pipeline	*pipeline;

	pipeline = init_pipeline();
	if (!pipeline)
		return (NULL);
	if (!create_commands(pipeline, token_list))
		return (NULL);
	if (!create_cmds_args(pipeline, token_list))
		return (NULL);
	return (pipeline);
}
