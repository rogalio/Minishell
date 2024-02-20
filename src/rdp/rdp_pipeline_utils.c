/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:36 by cabdli            #+#    #+#             */
/*   Updated: 2024/02/20 18:24:33 by cabdli           ###   ########.fr       */
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
			printf("In init_cmds_args\n");
			pipeline->commands->args_count++;
		}
		else if (token_list->token->type == TOKEN_REDIRECT)
			token_list = token_list->next;
		else
			pipeline->commands += 1;
		token_list = token_list->next;
	}
}

int	get_pipe_count(t_token_list *token_list)
{
	int	nb_pipe;

	nb_pipe = 0;
	while (token_list)
	{
		if (token_list->token->type == TOKEN_PIPE)
			nb_pipe++;
		token_list = token_list->next;
	}
	return (nb_pipe);
}
