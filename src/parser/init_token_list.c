/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:19:30 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:16:55 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include "utils.h"

t_token *find_next_token(const char **str)
{
    t_token *token;

    token = parse_token(*str);
    if (token)
        *str += ft_strlen(token->value);
    return token;
}

static void add_token_to_list(t_token_list **list, t_token *token)
{
    t_token_list *new_elem;
    t_token_list *temp;

    new_elem = new_token_list(token);
    if (!new_elem)
        return;
    if (!*list)
        *list = new_elem;
    else
    {
        temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_elem;
    }
}

t_token_list *init_token_list(const char *str)
{
    t_token_list *list;
    t_token *token;

    list = NULL;
    while (*str)
    {
        if (skip_whitespace(&str) == 0)
            break;
        if ((token = find_next_token(&str)))
            add_token_to_list(&list, token);
    }
    return list;
}

