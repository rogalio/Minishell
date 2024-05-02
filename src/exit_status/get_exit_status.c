/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:42:18 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 15:02:10 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"

int	convert_exit_status(char **word, t_minishell *minishell)
{
	char	*tmp;

	tmp = *word;
	if (g_exit_signal)
	{
		minishell->exit_status = g_exit_signal;
		g_exit_signal = 0;
	}
	*word = ft_itoa(minishell->exit_status);
	if (!(*word))
		return (*word = tmp, minishell->error = MALLOC, 0);
	free(tmp);
	return (1);
}

int	get_exit_status(t_pipeline *pipeline, t_minishell *minishell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < pipeline->command_count)
	{
		j = -1;
		while (++j < pipeline->commands[i]->args_count)
		{
			if (!ft_strcmp(pipeline->commands[i]->args[j], "$?"))
			{
				if (!convert_exit_status(&(pipeline->commands[i]->args[j]), \
				minishell))
				{
					minishell->exit_status = UNEXPEC_ERR;
					return (print_err_msg(&(minishell->error)), UNEXPEC_ERR);
				}
			}
		}
	}
	return (0);
}
