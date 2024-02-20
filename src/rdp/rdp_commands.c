/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:47:30 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 16:13:30 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	return (cmd);
}

/*
int	count_args(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	return (count);
}
*/

char	**allocate_new_args(t_command *cmd, int new_count)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * (new_count + 1));
	if (!new_args)
	{
		fprintf(stderr, "Allocation error in allocate_news_args\n");
		free_command(cmd);
		exit(EXIT_FAILURE);
	}
	return (new_args);
}

void	append_argument(char **args, int position, char *arg)
{
	args[position] = ft_strdup(arg);
	args[position + 1] = NULL;
}

// void	add_argument_to_command(t_command *command, char *arg)
// {
// 	new_args[count] = ft_strdup(arg);
// 	new_args[count + 1] = NULL;
// 	command->args = new_args;
// }

/*void	add_argument_to_command(t_command *command, char *arg)
{
	int		count;
	char	**new_args;

	count = count_args(command);
	new_args = realloc(command->args, sizeof(char *) * (count + 2));
	if (!new_args)
	{
		perror("Allocation error");
		free_command(command);
		exit(EXIT_FAILURE);
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	command->args = new_args;
}
*/
