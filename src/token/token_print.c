/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:09:42 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/13 19:12:57 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	print_token(const t_token *t)
{
	ft_printf(" type = %d, value = %s \n", t->type, t->value);
}

void	print_token_list(t_token_list *list)
{
	t_token_list	*temp;

	temp = list;
	while (temp)
	{
		print_token(temp->token);
		temp = temp->next;
	}
}
