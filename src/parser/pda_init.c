/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pda_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:42:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/26 18:23:33 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"

typedef enum e_state
{
  STATE_Q0,
  STATE_Q1,
  STATE_Q2,
  STATE_Q3,
  STATE_ERROR,
} t_state;

t_state transition_q0(t_token *token)
{
    if (token->type == TOKEN_WORD)
        return STATE_Q1;
    if (token->type == TOKEN_REDIRECT)
        return STATE_Q2;
    return STATE_ERROR;
}

t_state transition_q1(t_token *token)
{
    if (token->type == TOKEN_WORD)
        return STATE_Q1;
    if (token->type == TOKEN_REDIRECT)
        return STATE_Q2;
    if (token->type == TOKEN_PIPE)
        return STATE_Q3;
    return STATE_ERROR;
}

t_state transition_q2(t_token *token)
{
    if (token->type == TOKEN_WORD)
        return STATE_Q1;
    return STATE_ERROR;
}

t_state transition_q3(t_token *token)
{
    if (token->type == TOKEN_WORD)
        return STATE_Q1;
    if (token->type == TOKEN_REDIRECT)
        return STATE_Q2;
    return STATE_ERROR;
}


int validate_tokens(t_list *tokens)
{
    t_state state;
    t_token *token;

    state = STATE_Q0;

    while (tokens)
    {
        token = (t_token *)tokens->content;
        if (state == STATE_Q0)
            state = transition_q0(token);
        else if (state == STATE_Q1)
            state = transition_q1(token);
        else if (state == STATE_Q2)
            state = transition_q2(token);
        else if (state == STATE_Q3)
            state = transition_q3(token);
        else
            state = STATE_ERROR;
        if (state == STATE_ERROR)
            return (0);
        tokens = tokens->next;
    }
    return (state == STATE_Q0 || state == STATE_Q1);
}