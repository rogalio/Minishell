/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:19:30 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/11 14:26:59 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_token	*find_next_token(const char **str, t_error *error)
{
	t_token	*token;

	token = parse_token(*str, error);
	if (!token)
		return (NULL);
	*str += ft_strlen(token->value);
	return (token);
}

static int	add_token_to_list(t_token_list **list, t_token *token)
{
	t_token_list		*new;
	static t_token_list	*tmp;

	new = new_token_node(token);
	if (!new)
		return (0);
	new->token = token;
	if (!*list)
	{
		*list = new;
		tmp = *list;
	}
	else
	{
		tmp->next = new;
		tmp = tmp->next;
	}
	return (1);
}

t_token_list	*create_token_list(const char *str, t_error *error)
{
	t_token_list	*list;
	t_token			*token;

	list = NULL;
	while (*str)
	{
		if (skip_whitespace(&str) == 0)
			break ;
		token = find_next_token(&str, error);
		if (!token)
			return (free_token_list(list), NULL);
		if (!add_token_to_list(&list, token))
			return (free_token_list(list), NULL);
	}
	return (list);
}
