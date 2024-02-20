/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_pipeline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:36 by cabdli            #+#    #+#             */
/*   Updated: 2024/02/19 17:48:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	get_args_count(t_pipeline *pipeline, t_token_list *token_list, \
int *cmd)
{
	while (token_list)
	{
		if (token_list->token->type == TOKEN_WORD)
			pipeline->commands[*cmd]->args_count++;
		else if (token_list->token->type == TOKEN_REDIRECT)
			token_list = token_list->next->next;
		else
			*cmd++;
	}
}
