/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:44:00 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/13 15:38:36 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_current_directory(char *cwd)
{
	if (!cwd)
	{
		ft_putstr_fd("minishell: invalid path\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	pwd(t_data *data)
{
	char	*cwd;

	(void)data;
	cwd = getcwd(NULL, 0);
	if (check_current_directory(cwd))
		return (1);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (0);
}
