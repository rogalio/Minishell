/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:04:04 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 18:46:03 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "token.h"


void print_redirection_in(t_redirection_in *redirection_in)
{
  if (!redirection_in)
  {
    printf("No redirection in\n");
    return;
  }

  printf("Redirection in:\n");
  printf("Type: %s\n", redirection_in->type);
  printf("File: %s\n", redirection_in->file);
}

void print_redirection_out(t_redirection_out *redirection_out)
{
  if (!redirection_out)
  {
    printf("No redirection out\n");
    return;
  }

  printf("Redirection out:\n");
  printf("Type: %s\n", redirection_out->type);
  printf("File: %s\n", redirection_out->file);
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

  printf("Command with %d argument(s):\n", ft_strslen(cmd->args));
  for (int i = 0; cmd->args && cmd->args[i]; i++)
  {
    printf("Argument %d: %s\n", i + 1, cmd->args[i]);
  }
  print_redirection_in(cmd->redirect_in);
  print_redirection_out(cmd->redirect_out);
  printf("\n");
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