/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:30:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/02 15:51:26 by rogalio          ###   ########.fr       */
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

void free_token_list(t_token_list **list)
{
	t_token_list	*temp;
	t_token_list	*next;

	if (!list || !*list)
		return ;
	temp = *list;
	while (temp)
	{
		next = temp->next;
		free_token(temp->token);
		free(temp);
		temp = next;
	}
	*list = NULL;
}

void free_token_list22(t_token_list **list)
{
	t_token_list	*temp;
	t_token_list	*next;

	if (!list || !*list)
		return ;
	temp = *list;
	while (temp)
	{
		next = temp->next;
		free(temp->token->value);
		free(temp->token);
		free(temp);
		temp = next;
	}
	*list = NULL;
}
