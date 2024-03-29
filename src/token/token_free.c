/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:30:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/27 17:48:44 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"



static void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_token(tmp->token);
		free(tmp);
	}
}
