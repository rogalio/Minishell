/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:45:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/18 18:35:24 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (free(value), NULL);
	token->type = type;
	token->value = value;
	return (token);
}

t_token	*new_token_word(const char *str, t_error *error)
{
	char	*word;

	word = NULL;
	if (*str && (*str == '\'' || *str == '\"'))
		word = handle_qtes(str, error);
	else
		word = handle_rest(str, error);
	return (new_token(TOKEN_WORD, word));
}

t_token_list	*new_token_node(t_token *token)
{
	t_token_list	*new;

	new = ft_calloc(1, sizeof(t_token_list));
	if (!new)
		return (free_token(token), NULL);
	new->token = token;
	return (new);
}
