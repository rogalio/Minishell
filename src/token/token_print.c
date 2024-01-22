/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:21:48 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/22 18:23:13 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

void    token_print(const t_token *t)
{
  ft_printf((token_is_dynamic(t) ? "[%s]" : "%s"), t->value);
}
