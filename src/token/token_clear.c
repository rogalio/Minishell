/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:14:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/22 18:19:26 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void    token_clear(t_token *t)
{
	if (!token_is_dynamic(t))
		return ;
	ft_free(t->value);
	ft_free(t);
}
