/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:09:42 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/29 15:53:02 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	print_token(const t_token *token)
{
	printf("type: %d\n", token->type);
	printf("value: %s\n", token->value);

}

void	print_token_list(t_token_list *token_list)
{
	t_token_list	*tmp;

	tmp = token_list;
	while (tmp)
	{
		print_token(tmp->token);
		tmp = tmp->next;
	}
}
