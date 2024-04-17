/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:44:08 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/17 17:42:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static t_redirection	*init_redirection(void)
{
	t_redirection	*redirect;

	redirect = ft_calloc(1, sizeof(t_redirection));
	if (!redirect)
		return (NULL);
	return (redirect);
}

int	create_redirection(t_redirection **redirect, const char *type, \
const char *file)
{
	if (!(*redirect))
	{
		(*redirect) = init_redirection();
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
