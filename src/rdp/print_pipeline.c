/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:04:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/03 20:09:35 by rogalio          ###   ########.fr       */
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

void print_command(t_command *cmd)
{
  if (!cmd)
  {
    printf("Empty command\n");
    return;
  }

  printf("Command: ");
  for (int i = 0; cmd->args && cmd->args[i]; i++)
  {
    printf("%s ", cmd->args[i]);
  }
  printf("\n");

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
    printf("\n");
  }
}