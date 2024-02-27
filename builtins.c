/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:31:16 by cabdli            #+#    #+#             */
/*   Updated: 2024/02/27 15:33:42 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	built_echo(char **args)
{
	int	i;

	i = 1;
	if (!ft_strcmp(args[i], "-n"))
	{
		i++;
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				write(1, ' ', 1);
		}
	}
	else
	{
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				write(1, ' ', 1);
		}
		write(1, '\n', 1);
	}
}

/*
si cd est suivi d'args non valides, retourner un msg d'erreur
du type -> bash: cd: src/pwd: No such file or directory
si il y a plus d'un argument a la suite de cd -> bash: cd: too many arguments
*/
void	built_cd(t_command *cmd)
{
	if (cmd->args_count > 2)
		write()
}
