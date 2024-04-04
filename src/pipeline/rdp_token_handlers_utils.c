/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_token_handlers_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:13:26 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 13:50:18 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "parser.h"

int	get_nb_heredocs(t_token_list *tmp_list)
{
	int	nb_heredocs;

	nb_heredocs = 1;
	while (tmp_list && !ft_strcmp(tmp_list->token->value, "<<"))
	{
		nb_heredocs++;
		tmp_list = tmp_list->next->next;
	}
	return (nb_heredocs);
}

//Gestion erreur : fonction free a lancer en cas d'echec ?
t_heredoc	*create_heredoc(int nb_heredocs)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (perror("Allocation error"), NULL);
	// heredoc->type = NULL;
	heredoc->delimiter = ft_calloc((nb_heredocs + 1), sizeof(char *));
	heredoc->nb_heredocs = nb_heredocs;
	return (heredoc);
}
