/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:21:48 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/25 17:37:11 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void    token_print(const t_token *t)
{
  ft_printf("Token(type=%d, value=%s)\n", t->type, t->value);
}
