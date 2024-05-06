/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:29:58 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 18:34:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

void	print_numeric_arg_error(char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	restore_standard_descriptors(minishell->fd_out, minishell->fd_in);
	free_resources(minishell);
}
