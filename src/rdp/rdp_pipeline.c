/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:48:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 18:18:34 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

t_command	**init_commands(t_pipeline *pipeline, t_token_list *token_list)
{
	t_command	**commands;
	int			nb_cmd;

	nb_cmd = 0;
	pipeline->command_count = get_pipe_count(token_list) + 1;
	commands = malloc(pipeline->command_count * sizeof(t_command *));
	if (!commands)
		return (NULL);
	// while (nb_cmd < pipeline->command_count)
	// 	ft_bzero(commands[nb_cmd++], sizeof(t_command *));
	ft_bzero(commands, sizeof(t_command **));
	return (commands);
}

int	init_cmds_args(t_pipeline *pipeline, t_token_list *token_list)
{
	int	cmd;

	cmd = 0;
	get_args_count(pipeline, token_list);
	while (cmd < pipeline->command_count)
	{
		pipeline->commands[cmd]->args = \
		malloc((pipeline->commands[cmd]->args_count + 1) * sizeof(char *));
		if (!pipeline->commands[cmd]->args)
			return (0);
		ft_bzero(pipeline->commands[cmd]->args, sizeof(char **));
		cmd++;
	}
	return (1);
}

//mettre get_pipe_count dans init_commands ?
t_pipeline	*init_pipeline(t_token_list *token_list)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	//ft_bzero(pipeline, sizeof(t_pipeline));
	pipeline->commands = init_commands(pipeline, token_list);
	if (!pipeline->commands)
		return (NULL);
	if (!init_cmds_args(pipeline, token_list))
		return (NULL);
	return (pipeline);
}
/*
void	add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	t_command	**new_commands;

	new_commands = realloc(pipeline->commands, sizeof(t_command *) \
	* (pipeline->command_count + 1));
	if (!new_commands)
		printf("Allocation error in add_command_to_pipeline\n");
	pipeline->commands = new_commands;
	pipeline->commands[pipeline->command_count++] = cmd;
}
*/
