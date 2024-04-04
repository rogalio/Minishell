/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:36 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 15:24:40 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	get_args_count(t_pipeline *pipeline, t_token_list *token_list)
{
	int	cmd;

	cmd = 0;
	while (token_list)
	{
		if (token_list->token->type == TOKEN_WORD)
		{
			if (pipeline->commands && pipeline->commands[cmd])
					pipeline->commands[cmd]->args_count++;
		}
		else if (token_list->token->type == TOKEN_REDIRECT)
			token_list = token_list->next;
		else
			cmd += 1;
		token_list = token_list->next;
	}
}

int	get_pipe_count(t_token_list *token_list)
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
