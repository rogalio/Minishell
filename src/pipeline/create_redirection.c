/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:44:08 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 17:12:34 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static int	open_redirection(t_redirection *redirect)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(redirect->type, "<"))
		return (0);
	fd = open(redirect->file, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", STDERR_FILENO);
		return (perror(redirect->file), 1);
	}
	close(fd);
	return (0);
}

static t_redirection	*init_redirection(void)
{
	t_redirection	*redirect;

	redirect = ft_calloc(1, sizeof(t_redirection));
	if (!redirect)
		return (NULL);
	return (redirect);
}

int	create_redirection(t_redirection **redirect, const char *type, \
const char *file, t_env *env)
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
	if (!handle_expand_quotes(&((*redirect)->file), env))
		return (0);
	if (open_redirection(*redirect))
		return (0);
	return (1);
}
