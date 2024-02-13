/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:48:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 19:04:22 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = NULL;
	pipeline->command_count = 0;
	return (pipeline);
}

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
