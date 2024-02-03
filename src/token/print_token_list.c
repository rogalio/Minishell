/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:09:42 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/03 19:26:33 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void print_token_list(t_token_list *list)
{
    t_token_list *temp;

    temp = list;
    while (temp)
    {
        print_token(temp->token);
        temp = temp->next;
    }
}