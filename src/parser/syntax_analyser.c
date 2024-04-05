/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:42:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 13:08:31 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_state	transition_q0(t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (STATE_Q1);
	else if (token->type == TOKEN_REDIRECT)
		return (STATE_Q2);
	return (STATE_ERROR);
}

t_state	transition_q1(t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (STATE_Q1);
	if (token->type == TOKEN_REDIRECT)
		return (STATE_Q2);
	if (token->type == TOKEN_PIPE)
		return (STATE_Q3);
	return (STATE_ERROR);
}

t_state	transition_q2(t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (STATE_Q1);
	return (STATE_ERROR);
}

t_state	transition_q3(t_token *token)
{
	if (token->type == TOKEN_WORD)
		return (STATE_Q1);
	if (token->type == TOKEN_REDIRECT)
		return (STATE_Q2);
	return (STATE_ERROR);
}

int	syntax_analyzer(t_token_list *token_list, t_error *error)
{
	t_state	state;
	t_token	*token;

	state = STATE_Q0;
	token = NULL;
	while (token_list)
	{
		token = token_list->token;
		if (state == STATE_Q0)
			state = transition_q0(token);
		else if (state == STATE_Q1)
			state = transition_q1(token);
		else if (state == STATE_Q2)
			state = transition_q2(token);
		else if (state == STATE_Q3)
			state = transition_q3(token);
		if (state == STATE_ERROR)
			return (*error = SYNTAX, 0);
		token_list = token_list->next;
	}
	if (state != STATE_Q1)
		return (*error = SYNTAX, 0);
	return (1);
}
