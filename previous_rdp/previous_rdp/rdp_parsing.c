/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 13:29:20 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"

void	handle_token(t_token_list **token_list, t_pipeline *pipeline, \
int *index, t_env *env)
{
	if ((*token_list)->token->type == TOKEN_WORD)
		handle_word(index, (*token_list)->token->value, pipeline, env);
	else if ((*token_list)->token->type == TOKEN_REDIRECT)
		handle_redirection(token_list, pipeline->commands[index[0]]);
	else
	{
		index[0]++;
		index[1] = 0;
	}
}

void	fill_pipeline(t_token_list *token_list, t_pipeline	\
*pipeline, t_env *env)
{
	int	index[2];

	index[0] = 0;
	index[1] = 0;
	while (token_list)
	{
		handle_token(&token_list, pipeline, index, env);
		token_list = token_list->next;
	}
}


t_pipeline	*parse_rdp(t_token_list *token_list, t_env *env)
{
	t_pipeline	*pipeline;

	pipeline = NULL;
	pipeline = create_pipeline(token_list);
	if (!pipeline)
		return (NULL);
	fill_pipeline(token_list, pipeline, env);
	return (pipeline);
}
