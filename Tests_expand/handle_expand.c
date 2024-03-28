/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 13:59:06 by cabdli           ###   ########.fr       */
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

void	handle_expand(char **word, char *new_word, char *var_value, int *ij)
{
	ij[0]++;
	if ((*word)[ij[0]] == '?')
	{
		ij[0]++;
		new_word[ij[1]++] = '0';
		return ;
	}
	replace_variable(&new_word, var_value, &ij[1]);
}
