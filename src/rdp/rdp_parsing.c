/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/28 16:27:39 by rogalio          ###   ########.fr       */
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

/*
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
*/



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

	commands = ft_calloc(command_count, sizeof(t_command *));
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
	cmd->args = NULL;
	cmd->args_count = 0;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->heredoc = NULL;
	return (cmd);
}

/*

typedef struct s_redirection
{
	char	*type;
	char	*file;
}t_redirection;

typedef struct s_heredoc
{
	char	*type;
	char	**delimiter;
	int		nb_heredocs;
}t_heredoc;

typedef struct s_command
{
	char			**args;
	int				args_count;
	t_redirection	*redirect_in;
	t_redirection	*redirect_out;
	t_heredoc		*heredoc;
}t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			command_count;
}t_pipeline;

*/

void free_redirection(t_redirection *redirection)
{
    if (!redirection)
        return;
    free(redirection->type);
    free(redirection->file);
    free(redirection);
}

void free_heredoc(t_heredoc *heredoc)
{
    int i;

    if (!heredoc)
        return;
    free(heredoc->type);
    if (heredoc->delimiter)
    {
        i = 0;
        while (i < heredoc->nb_heredocs)
        {
            free(heredoc->delimiter[i]);
            i++;
        }
        free(heredoc->delimiter);
    }
    free(heredoc);
}

void free_command(t_command *command)
{
    int i;

    if (!command)
        return;
    if (command->args)
    {
        i = 0;
        while (i < command->args_count)
        {
            free(command->args[i]);
            i++;
        }
        free(command->args);
    }
    free_redirection(command->redirect_in);
    free_redirection(command->redirect_out);
    free_heredoc(command->heredoc);
    free(command);
}

void free_commands(t_command **commands, int command_count)
{
    int i;

    if (!commands)
        return;
    i = 0;
    while (i < command_count)
    {
        free_command(commands[i]);
        i++;
    }
    free(commands);
}

void free_pipeline(t_pipeline *pipeline)
{
		if (!pipeline)
				return;
		free_commands(pipeline->commands, pipeline->command_count);
		free(pipeline);
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
			printf("nb_cmd: %d\n", nb_cmd);
        pipeline->commands[nb_cmd] = init_command();
        if (!pipeline->commands[nb_cmd])
        {
            free_commands(pipeline->commands, nb_cmd);
            pipeline->commands = NULL;
            return (0);
        }
        nb_cmd++;
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
	/*
	if (!create_commands(pipeline, token_list))
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	*/

	//fill_pipeline(token_list, pipeline, env);
	return (pipeline);
}
