/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:09:42 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 17:47:54 by cabdli           ###   ########.fr       */
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
	int				i;
	t_token_list	*tmp;

	i = 1;
	tmp = token_list;
	while (tmp)
	{
		printf("Token %d\n", i++);
		print_token(tmp->token);
		tmp = tmp->next;
	}
}
