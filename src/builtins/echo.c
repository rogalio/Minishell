/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:43 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 13:49:05 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipeline.h"

int	echo(t_data *data)
{
	int	i;

	i = 1;
	if (!ft_strcmp(data->args[i], "-n"))
	{
		i++;
		while (data->args[i])
		{
			ft_putstr_fd(data->args[i++], 1);
			if (data->args[i])
				write(1, " ", 1);
		}
	}
	else
	{
		while (data->args[i])
		{
			ft_putstr_fd(data->args[i++], STDOUT_FILENO);
			if (data->args[i])
				write(1, " ", STDOUT_FILENO);
		}
		write(1, "\n", STDOUT_FILENO);
	}
	return (0);
}
