/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_dynamic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:12:59 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/22 18:01:02 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool		token_is_dynamic(const t_token *t)
{
  return (t->type == TOKEN_WORD || t->type == TOKEN_MULTILINE);
}
