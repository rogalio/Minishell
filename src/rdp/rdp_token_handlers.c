/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_token_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:46:02 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/19 17:58:34 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "parser.h"

void	init_redirection(t_redirection **redirect, const char *type, \
const char *file)
{
	if (!(*redirect))
	{
		(*redirect) = malloc(sizeof(t_redirection));
		if (!(*redirect))
		{
			perror("Allocation error");
			exit(EXIT_FAILURE);
		}
		(*redirect)->type = NULL;
		(*redirect)->file = NULL;
	}
	else
	{
		free((*redirect)->type);
		free((*redirect)->file);
	}
	(*redirect)->type = ft_strdup(type);
	(*redirect)->file = ft_strdup(file);
}

void	handle_redirection(t_token_list **token_list, t_command *command)
{
	char	*type;
	char	*file;

	type = (*token_list)->token->value;
	*token_list = (*token_list)->next;
	file = (*token_list)->token->value;

	if (ft_strcmp(type, "<") == 0 || ft_strcmp(type, "<<") == 0)
		init_redirection(&command->redirect_in, type, file);
	else if (ft_strcmp(type, ">") == 0 || ft_strcmp(type, ">>") == 0)
		init_redirection(&command->redirect_out, type, file);
}


void	handle_word(t_command **current_command, char *word, char **envp)
{
	//if (!*current_command)
		//*current_command = create_command();
	expand_variables_and_handle_quotes(&word, envp);
	add_argument_to_command(*current_command, word);
}

/*
void	handle_pipe(t_pipeline *pipeline, t_command **current_command)
{
	if (!*current_command)
		return ;
	add_command_to_pipeline(pipeline, *current_command);
	*current_command = create_command();
}
*/
