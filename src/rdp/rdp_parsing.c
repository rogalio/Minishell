/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/08 20:24:06 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"
#include <stdio.h>


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





int count_pipes(t_token_list *token_list)
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

// init_commands
t_command	**init_commands(int command_count)
{
	t_command	**commands;

	commands = ft_calloc(command_count + 1, sizeof(t_command *));
	if (!commands)
		return (NULL);
	return (commands);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	return (cmd);
}


int create_commands(t_pipeline *pipeline, t_token_list *token_list)
{
    int	nb_cmd;

		nb_cmd = 0;
    pipeline->command_count = count_pipes(token_list) + 1;
    pipeline->commands = init_commands(pipeline->command_count);
    if (!pipeline->commands)
        return (0);
    while (nb_cmd < pipeline->command_count)
    {
        pipeline->commands[nb_cmd] = init_command();
        if (!pipeline->commands[nb_cmd])
        {
            free_commands(pipeline->commands, nb_cmd);
            //pipeline->commands = NULL;
            return (0);
        }
        nb_cmd++;
    }
    return (1);
}


char    **init_cmds_args2(int args_count)
{
    char    **args;

    args = ft_calloc((args_count + 1), sizeof(char *));
    if (!args)
        return (NULL);
    return (args);
}


int    create_cmds_args2(t_pipeline *pipeline, t_token_list *token_list)
{
    int    cmd;

    cmd = -1;
    get_args_count(pipeline, token_list);
    while (++cmd < pipeline->command_count)
    {
        pipeline->commands[cmd]->args = init_cmds_args2 \
        (pipeline->commands[cmd]->args_count);
        if (!pipeline->commands[cmd]->args)
            return (0);
    }
    return (1);
}


t_pipeline	*create_pipeline2(t_token_list *token_list, t_env *env)
{
	t_pipeline	*pipeline;
	(void)env;
	(void)token_list;

	pipeline = NULL;
	pipeline = init_pipeline();
	if (!pipeline)
		return (NULL);
	if (!create_commands(pipeline, token_list))
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	if (!create_cmds_args2(pipeline, token_list))
	{
		free_pipeline(pipeline);
		return (NULL);
	}

	fill_pipeline(token_list, pipeline, env);
	return (pipeline);
}
