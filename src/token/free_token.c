/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:30:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 17:58:32 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*temp;

	temp = NULL;
	if (!list)
		return ;
	while (list)
	{
		temp = list;
		list = list->next;
		free_token(temp->token);
		free(temp);
	}
	list = NULL;
}
