/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:20:13 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/13 15:36:51 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// modifier ce code pour qu'il fonctionne et gerer le free en cas de success()
int	exit_shell(t_data *data)
{
	if (data->args[1])
	{
		if (data->args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		if (ft_isnumber(data->args[1]) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		return (ft_atoi(data->args[1]));
	}
	return (0);
}






