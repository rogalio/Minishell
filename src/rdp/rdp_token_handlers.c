/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_token_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:46:02 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/14 13:25:54 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "parser.h"
#include "builtins.h"

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

void	init_heredoc(t_token_list **token_list, t_heredoc **heredoc, \
char *type)
{
	t_token_list	*tmp_list;
	int				nb_heredocs;
	int				i;

	tmp_list = (*token_list)->next;
	nb_heredocs = 1;
	i = 0;
	nb_heredocs = get_nb_heredocs(tmp_list);
	(*heredoc) = create_heredoc(nb_heredocs);
	if (!(*heredoc))
		exit(EXIT_FAILURE);
	(*heredoc)->type = ft_strdup(type);
	while (i < nb_heredocs)
	{
		(*heredoc)->delimiter[i] = ft_strdup((*token_list)->token->value);
		if ((nb_heredocs > 1) && (i != (nb_heredocs - 1)))
			*token_list = (*token_list)->next->next;
		i++;
	}
}

void	handle_redirection(t_token_list **token_list, t_command *command)
{
	char	*type;
	char	*file;

	type = (*token_list)->token->value;
	*token_list = (*token_list)->next;
	file = (*token_list)->token->value;

	if (ft_strcmp(type, "<") == 0)
		init_redirection(&command->redirect_in, type, file);
	else if (ft_strcmp(type, ">") == 0 || ft_strcmp(type, ">>") == 0)
		init_redirection(&command->redirect_out, type, file);
	else if (ft_strcmp(type, "<<") == 0)
		init_heredoc(token_list, &command->heredoc, type);
}

void	handle_word(int *index, char *word, t_pipeline *pipeline, t_env *env)
{
	expand_variables_and_handle_quotes(&word, env);
	pipeline->commands[index[0]]->args[index[1]] = ft_strdup(word);
	index[1]++;
}
