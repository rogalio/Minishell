/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/28 15:45:34 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

static void	replace_variable(char **new_word, char *var_value, int *j)
{
	int	i;

	i = -1;
	if (strcmp(var_value, "Value not found"))
	{
		while (var_value[++i])
			(*new_word)[(*j)++] = var_value[i];
	}
}

void	handle_expand(char *word, t_expansion *exp, int *ije)
{
	ije[0]++;
	if (word[ije[0]] == '?')
	{
		ije[0]++;
		exp->new_word[ije[1]++] = '0';
		return ;
	}
	ije[0] += strlen(exp->var_name[ije[2]]);
	replace_variable(&(exp->new_word), exp->var_value[ije[2]++], &ije[1]);
}
