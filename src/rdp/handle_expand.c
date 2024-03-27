/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 11:33:46 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

static void	replace_variable(char **new_word, char *var_value, int *j)
{
	int	i;

	i = -1;
	if (var_value)
	{
		while (var_value[++i])
			(*new_word)[(*j)++] = var_value[i];
	}
}

void	handle_expand(char **word, char *new_word, char *var_value, int *i, int *j)
{
	(*i)++;
	if ((*word)[*i] == '?')
	{
		(*i)++;
		new_word[(*j)++] = '0';
		return ;
	}
	replace_variable(&new_word, var_value, j);
}
