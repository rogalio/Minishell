/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:24:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/21 15:38:36 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void get_path(t_data *data, char **path)
{
  if (data->args[1] == NULL)
    *path = getenv("HOME");
  else
    *path = data->args[1];
}

int cd(t_data *data)
{
  char *path;

  get_path(data, &path);
  if (chdir(path) == -1)
  {
    ft_putstr_fd("cd: ", 2);
    perror(path);
    return (1);
  }
  return (0);
}
