/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:47:01 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/24 17:03:52 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	print_err_msg(t_error *error)
{
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	if (*error == QUOTES)
		str = "minishell: error: unclosed quotes\n";
	else if (*error == SYNTAX)
		str = "minishell: syntax error near unexpected token\n";
	else if (*error == HDOC_SIGN)
	{
		str = "minishell: warning: here-document delimited by end-of-file ";
		str2 = "(wanted: delimiter)\n";
	}
	else
		str = "minishell: error: malloc failure\n";
	ft_putstr_fd(str, STDERR_FILENO);
	if (str2)
		ft_putstr_fd(str2, STDERR_FILENO);
}
