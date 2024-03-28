/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:55:15 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 16:11:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	free_var_name(char **var_name)
{
	char	*tmp;

	tmp = NULL;
	while (*var_name)
	{
		tmp = *var_name;
		var_name++;
		free(tmp);
	}
}

void	free_var_value(char **var_value)
{
	char	*tmp;

	tmp = NULL;
	while (*var_value)
	{
		tmp = *var_value;
		var_value++;
		free(tmp);
	}
}

void	free_expansion(t_expansion *exp)
{
	if (exp)
	{
		if (exp->var_name)
		{
			free_var_name(exp->var_name);
			free(exp->var_name);
		}
		if (exp->var_value)
		{
			free_var_value(exp->var_value);
			free(exp->var_value);
		}
		if (exp->new_word)
			free(exp->new_word);
		free(exp);
	}
}
