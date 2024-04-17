/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:54:21 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/17 19:23:23 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

#include <fcntl.h>

// generate random name
char    *generate_random_name(void)
{
        int     i;
        int     fd;
        char    *name;
        char    c;

        i = 1;
        name = ft_calloc(8, sizeof(char));
        if (!name)
                return (NULL);
        fd = open("/dev/random", O_RDONLY);
        if (fd == -1)
                return (free(name), NULL);
        while (i < 7)
        {
                if (read(fd, &c, 1) == -1)
                        return (free(name), close(fd), NULL);
                if (ft_isalnum(c))
                        name[i++] = c;
        }
        close(fd);
        name[0] = '.';
        return (name);
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

static t_heredoc	**init_heredocs(int nb_heredocs)
{
	t_heredoc	**heredoc;

	heredoc = ft_calloc((nb_heredocs + 1), sizeof(t_heredoc *));
	if (!heredoc)
		return (NULL);
	return (heredoc);
}

static t_heredoc	*init_hdcs(void)
{
	t_heredoc	*hdcs;

	hdcs = ft_calloc(1, sizeof(t_heredoc));
	if (!hdcs)
		return (NULL);
	return (hdcs);
}

static int	fill_heredocs(int nb_heredocs, t_heredoc **heredoc, t_token_list \
**token_list)
{
	int	i;

	i = -1;
	while (++i < nb_heredocs)
	{
		heredoc[i]->delimiter = ft_strdup((*token_list)->token->value);
		if (!heredoc[i]->delimiter)
			return (0);
		heredoc[i]->hdoc_name = generate_random_name();
		if (!heredoc[i]->hdoc_name)
			return (0);
		if ((nb_heredocs > 1) && (i != ((nb_heredocs) - 1)))
			(*token_list) = (*token_list)->next->next;
	}
	return (1);
}

int	create_heredoc(t_token_list **token_list, t_heredoc ***heredoc, \
t_command *command)
{
	int	nb_hdcs;

	nb_hdcs = -1;
	command->nb_heredocs = get_nb_heredocs((*token_list)->next);
	(*heredoc) = init_heredocs(command->nb_heredocs);
	if (!(*heredoc))
		return (0);
	while (++nb_hdcs < command->nb_heredocs)
	{
		(*heredoc)[nb_hdcs] = init_hdcs();
		if (!(*heredoc)[nb_hdcs])
			return (0);
	}
	if (!fill_heredocs(command->nb_heredocs, (*heredoc), token_list))
		return (0);
	return (1);
}
