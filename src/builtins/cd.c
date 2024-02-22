/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:24:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/22 17:00:44 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void get_path(t_data *data, char **path)
{
  if (!data->args[1])
  {
    *path = get_env_var(data->env, "HOME");
    if (!*path)
      *path = ".";
  }
  else if (strcmp(data->args[1], "-") == 0)
  {
    *path = get_env_var(data->env, "OLDPWD");
    if (!*path)
      *path = ".";
  }
  else
    *path = data->args[1];
}

int cd(t_data *data)
{
  char *path;
  char *cwd;

  get_path(data, &path);
  if (chdir(path) == -1)
  {
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    return (1);
  }
  cwd = getcwd(NULL, 0);
  if (!cwd)
  {
    ft_putstr_fd("minishell: cd: invalid path\n", STDERR_FILENO);
    return (1);
  }
  set_env_var(data->env, "OLDPWD", get_env_var(data->env, "PWD"));
  set_env_var(data->env, "PWD", cwd);
  free(cwd);
  print_env(data->env);
  return (0);
}
