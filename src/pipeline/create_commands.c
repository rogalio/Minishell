/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:45 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/06 13:22:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static int	count_pipes(t_token_list *token_list)
{
	int	pipe_count;

	pipe_count = 0;
	while (token_list)
	{
		if (token_list->token->type == TOKEN_PIPE)
			pipe_count++;
		token_list = token_list->next;
	}
	return (pipe_count);
}

static t_command	**init_commands(int command_count)
{
	t_command	**commands;

	commands = ft_calloc((command_count + 1), sizeof(t_command *));
	if (!commands)
		return (NULL);
	return (commands);
}

static t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	create_commands(t_pipeline *pipeline, t_token_list *token_list)
{
	int	nb_cmd;

	nb_cmd = -1;
	pipeline->command_count = count_pipes(token_list) + 1;
	pipeline->commands = init_commands(pipeline->command_count);
	if (!pipeline->commands)
		return (free_pipeline(pipeline), 0);
	while (++nb_cmd < pipeline->command_count)
	{
		pipeline->commands[nb_cmd] = init_cmd();
		if (!pipeline->commands[nb_cmd])
			return (free_commands(pipeline->commands, nb_cmd), 0);
	}
	return (1);
}
