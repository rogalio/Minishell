/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:55:15 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 13:52:58 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	free_exp_tab(char **exp_tab)
{
	char	*tmp;

	tmp = NULL;
	while (*exp_tab)
	{
		tmp = *exp_tab;
		exp_tab++;
		free(tmp);
	}
}

void	free_expansion(t_expansion *exp)
{
	if (exp)
	{
		if (exp->var_name)
		{
			free_exp_tab(exp->var_name);
			free(exp->var_name);
		}
		if (exp->var_value)
		{
			free_exp_tab(exp->var_value);
			free(exp->var_value);
		}
		free(exp);
	}
}
