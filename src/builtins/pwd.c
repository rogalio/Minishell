/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:44:00 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/02 15:13:09 by cabdli           ###   ########.fr       */
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

int	pwd(t_data *data, t_minishell *minishell)
{
	char	*cwd;

	(void)data;
	(void)minishell;
	cwd = getcwd(NULL, 0);
	if (check_current_directory(cwd))
		return (UNEXPEC_ERR);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (SUCCESS);
}
