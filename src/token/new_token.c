/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:45:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/03 19:20:52 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token    *new_token(t_token_type type, char *value)
{
  t_token		*t;

  if (!(t = (t_token *)malloc(sizeof(t_token))))
    return (NULL);
  t->type = type;
  t->value = value;
  return (t);
}
