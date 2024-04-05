/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:39:39 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/05 17:03:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static int	handle_word(int *cmd_arg, char *word, t_pipeline *pipeline, \
t_env *env)
{
	if (expand_quotes(word))
		handle_expand_quotes(&word, env);
	pipeline->commands[cmd_arg[0]]->args[cmd_arg[1]] = ft_strdup(word);
	if (!(pipeline->commands[cmd_arg[0]]->args[cmd_arg[1]]))
		return (0);
	cmd_arg[1]++;
	return (1);
}

static int	handle_redirection(t_token_list **token_list, t_command *command)
{
	char	*type;
	char	*file;

	type = (*token_list)->token->value;
	*token_list = (*token_list)->next;
	file = (*token_list)->token->value;
	if (ft_strcmp(type, ">") == 0 || ft_strcmp(type, ">>") == 0)
	{
		if (!init_redirection(&command->redirect_out, type, file))
			return (0);
	}
	else if (ft_strcmp(type, "<") == 0)
	{
		if (!init_redirection(&command->redirect_in, type, file))
			return (0);
	}
	else if (ft_strcmp(type, "<<") == 0)
	{
		if (!init_heredoc(token_list, &command->heredoc, type))
			return (0);
	}
	return (1);
}

static void	handle_pipe(int *cmd_arg)
{
	cmd_arg[0]++;
	cmd_arg[1] = 0;
}

static int	handle_token(t_token_list **token_list, t_pipeline *pipeline, \
int *cmd_arg, t_env *env)
{
	if ((*token_list)->token->type == TOKEN_WORD)
	{
		if (!handle_word(cmd_arg, (*token_list)->token->value, pipeline, env))
			return (0);
	}
	else if ((*token_list)->token->type == TOKEN_REDIRECT)
	{
		if (!handle_redirection(token_list, pipeline->commands[cmd_arg[0]]))
			return (0);
	}
	else
		handle_pipe(cmd_arg);
	return (1);
}

int	fill_pipeline(t_token_list *token_list, t_pipeline	\
*pipeline, t_env *env)
{
	int	cmd_arg[2];

	ft_bzero(cmd_arg, sizeof(cmd_arg));
	while (token_list)
	{
		if (!handle_token(&token_list, pipeline, cmd_arg, env))
			return (0);
		token_list = token_list->next;
	}
	return (1);
}
