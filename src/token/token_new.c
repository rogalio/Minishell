/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:45:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:35:46 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token    *new_token(t_token_type type, char *value)
{
  t_token		*t;

  if (!(t = (t_token *)malloc(sizeof(t_token))))
    return (NULL);
  t->type = type;
  t->value = value;
  return (t);
}

t_token_list *new_token_list(t_token *token)
{
    t_token_list *new_elem;

    new_elem = malloc(sizeof(t_token_list));
    if (!new_elem)
        return NULL;
    new_elem->token = token;
    new_elem->next = NULL;
    return new_elem;
}

t_token *new_word_token(const char *str)
{
    char *word;
    int i;

    i = 0;
    while (str[i] && !ft_isspace(str[i]))
        i++;
    word = ft_strndup(str, i);
    return new_token(TOKEN_WORD, word);
}
