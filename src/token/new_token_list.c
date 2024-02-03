/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:54:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/03 19:24:54 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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