/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:04:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 17:23:05 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "token.h"


void print_redirection(t_redirection *redirect)
{
  if (redirect)
  {
    printf("Redirection type: %s, file: %s\n", redirect->type, redirect->file);
  }
  else
  {
    printf("No redirection\n");
  }
}

int ft_strslen(char **strs)
{
  int i;

  i = 0;
  while (strs[i])
    i++;
  return (i);
}

void print_command(t_command *cmd)
{
  if (!cmd)
  {
    printf("Empty command\n");
    return;
  }

  for (int i = 0; i < ft_strslen(cmd->args); i++)
  {
    printf("Argument %d: %s\n", i + 1, cmd->args[i]);
  }
  print_redirection(cmd->redirect);
}

void print_pipeline(t_pipeline *pipeline)
{
  if (!pipeline)
  {
    printf("Empty pipeline\n");
    return;
  }

  printf("Pipeline with %d command(s):\n", pipeline->command_count);
  for (int i = 0; i < pipeline->command_count; i++)
  {
    printf("Command %d:\n", i + 1);
    print_command(pipeline->commands[i]);
  }

}