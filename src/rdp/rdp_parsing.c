/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 19:03:22 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"

void	handle_token(t_token_list **token_list, t_pipeline *pipeline, \
t_command **current_command, char **envp)
{
	if ((*token_list)->token->type == TOKEN_WORD)
		handle_word(current_command, (*token_list)->token->value, envp);
	else if ((*token_list)->token->type == TOKEN_REDIRECT)
		handle_redirection(token_list, *current_command);
	else
		handle_pipe(pipeline, current_command);
}

t_pipeline	*parse_rdp(t_token_list *token_list, char **envp)
{
	t_pipeline	*pipeline;
	t_command	*last_command;

	pipeline = init_pipeline();
	last_command = NULL;
	while (token_list)
	{
		handle_token(&token_list, pipeline, &last_command, envp);
		token_list = token_list->next;
	}
	if (last_command)
		add_command_to_pipeline(pipeline, last_command);
	return (pipeline);
}
