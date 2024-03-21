/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:45:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/21 13:24:59 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = value;
	return (t);
}

t_token_list	*new_token_list(t_token *token)
{
	t_token_list	*new_elem;

	new_elem = ft_calloc(1, sizeof(t_token_list *));
	if (!new_elem)
		return (NULL);
	new_elem->token = token;
	// new_elem->next = NULL;
	return (new_elem);
}

t_token	*new_word_token(const char *str)
{
	char	*word;
	int		i;

	i = 0;
	word = NULL;
	if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		word = handle_quotes(str);
	else
		word = handle_rest(str);
	return (new_token(TOKEN_WORD, word));
}
