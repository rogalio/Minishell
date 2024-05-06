/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:20:13 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/03 17:57:04 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

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

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	free_env(&(*data)->env);
	free(*data);
	*data = NULL;
}

void	free_minishell(t_minishell **minishell)
{
	if (!minishell || !*minishell)
		return ;
	free_data(&(*minishell)->data);
	free(*minishell);
	*minishell = NULL;
}

void	free_resources(t_minishell *minishell)
{
	free_token_list(&minishell->token_list);
	free_pipeline(&minishell->pipeline);
	free_minishell(&minishell);
}

int	exit_shell(t_data *data, t_minishell *minishell)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", 2);
	if (data->args[1])
	{
		if (!ft_isnumber(data->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			restore_standard_descriptors(minishell->fd_out, minishell->fd_in);
			free_resources(minishell);
			exit(SYNTAX_ERR);
		}
		if (data->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		exit_code = ft_atoi(data->args[1]);
		restore_standard_descriptors(minishell->fd_out, minishell->fd_in);
		free_resources(minishell);
		exit(exit_code);
	}
	exit_code = minishell->exit_status;
	restore_standard_descriptors(minishell->fd_out, minishell->fd_in);
	free_resources(minishell);
	exit(exit_code);
}
