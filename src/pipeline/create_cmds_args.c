/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:21:09 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/05 15:29:33 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static void	get_args_count(t_pipeline *pipeline, t_token_list *token_list)
{
	int	cmd;

	cmd = 0;
	while (token_list && cmd < pipeline->command_count)
	{
		if (token_list->token->type == TOKEN_WORD)
			pipeline->commands[cmd]->args_count++;
		else if (token_list->token->type == TOKEN_REDIRECT)
			token_list = token_list->next;
		else
			cmd += 1;
		token_list = token_list->next;
	}
}

static char	**init_cmds_args(int args_count)
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
