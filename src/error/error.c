/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:47:01 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/05 13:03:30 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	print_err_msg(t_error *error)
{
	if (*error == QUOTES)
		ft_putstr_fd("Error: unclosed quotes\n", STDERR_FILENO);
	else if (*error == SYNTAX)
		ft_putstr_fd("minishell: syntax error near unexpected token\n", \
		STDERR_FILENO);
	else
		ft_putstr_fd("Error: malloc failure\n", STDERR_FILENO);
}
