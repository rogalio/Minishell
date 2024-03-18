/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:59:21 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/15 15:17:11 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"



int	export(t_data *data)
{
  int		i;
  t_env	*new_node;

  i = 1;
  while (data->args[i])
  {
    new_node = create_env_node(data->args[i]);
    if (!new_node)
      return (1);
    data->env = add_to_env_list(data->env, new_node);
    i++;
  }
  return (0);
}
