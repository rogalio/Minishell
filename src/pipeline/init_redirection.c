/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:54:21 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/05 17:05:54 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

int	init_redirection(t_redirection **redirect, const char *type, \
const char *file)
{
	if (!(*redirect))
	{
		(*redirect) = ft_calloc(1, sizeof(t_redirection));
		if (!(*redirect))
			return (0);
	}
	else
	{
		free((*redirect)->type);
		free((*redirect)->file);
	}
	(*redirect)->type = ft_strdup(type);
	if (!(*redirect)->type)
		return (0);
	(*redirect)->file = ft_strdup(file);
	if (!(*redirect)->file)
		return (0);
	return (1);
}

static int	get_nb_heredocs(t_token_list *token_list)
{
	int	nb_heredocs;

	nb_heredocs = 1;
	while (token_list && !ft_strcmp(token_list->token->value, "<<"))
	{
		nb_heredocs++;
		token_list = token_list->next->next;
	}
	return (nb_heredocs);
}

static t_heredoc	*create_heredoc(int nb_heredocs, char *type)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = ft_calloc((nb_heredocs + 1), sizeof(char *));
	if (!heredoc->delimiter)
		return (NULL);
	heredoc->nb_heredocs = nb_heredocs;
	heredoc->type = ft_strdup(type);
	if (!heredoc->type)
		return (NULL);
	return (heredoc);
}

static int	fill_delimiter(int nb_heredocs, char **delimiter, t_token_list \
**token_list)
{
	int	i;

	i = 0;
	while (i < nb_heredocs)
	{
		delimiter[i] = ft_strdup((*token_list)->token->value);
		if (!delimiter[i])
			return (0);
		if ((nb_heredocs > 1) && (i != ((nb_heredocs) - 1)))
			(*token_list) = (*token_list)->next->next;
		i++;
	}
	return (1);
}

int	init_heredoc(t_token_list **token_list, t_heredoc **heredoc, \
char *type)
{
	(*heredoc) = create_heredoc(get_nb_heredocs((*token_list)->next), type);
	if (!(*heredoc))
		return (0);
	if (!fill_delimiter((*heredoc)->nb_heredocs, (*heredoc)->delimiter, \
	token_list))
		return (0);
	return (1);
}
