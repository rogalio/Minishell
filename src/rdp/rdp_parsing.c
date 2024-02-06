/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 17:18:18 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include <stdio.h>
#include "rdp.h"



void handle_token(t_token_list **tokens, t_pipeline *pipeline, t_command **current_command, char **envp)
{
    if ((*tokens)->token->type == TOKEN_WORD)
        handle_word(current_command, (*tokens)->token->value, envp);
    else if ((*tokens)->token->type == TOKEN_REDIRECT)
        handle_redirection(tokens, *current_command);
    else if ((*tokens)->token->type == TOKEN_PIPE)
        handle_pipe(pipeline, current_command);
}


t_pipeline *parse_rdp(t_token_list *tokens, char **envp)
{
        t_pipeline *pipeline;
        t_command *last_command;

        pipeline = init_pipeline();
        last_command = NULL;

        while (tokens)
        {
            handle_token(&tokens, pipeline, &last_command, envp);
            tokens = tokens->next;
        }
        if (last_command)
            add_command_to_pipeline(pipeline, last_command);
        return pipeline;
}