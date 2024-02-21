/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:43 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/21 15:15:28 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void echo(t_data *data)
{
  int i;
  int new_line;

  i = 1;
  new_line = 1;
  // Vérification de l'option '-n' au début
  if (data->args[i] && !strcmp(data->args[i], "-n"))
  {
    new_line = 0;
    i++;
  }
  // Parcours et affichage des arguments
  while (data->args[i])
  {
    ft_putstr_fd(data->args[i], STDOUT_FILENO);
    if (data->args[i + 1])
      ft_putstr_fd(" ", STDOUT_FILENO);
    i++;
  }
  // Si '-n' n'est pas présent, on ajoute un newline à la fin
  if (new_line)
    ft_putstr_fd("\n", 1);
}
