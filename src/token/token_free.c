/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:30:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/25 14:00:03 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	free_token(t_token *token)
{
	free(token->value);
	// free(token->type);
	free(token);
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free_token(temp->token);
		free(temp);
	}
	free(list);
}
