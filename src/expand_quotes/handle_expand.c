/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/26 12:38:34 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

int	get_nb_expand(char *word)
{
	int	i;
	int	expand;

	i = -1;
	expand = 0;
	while (word[++i])
	{
		if (word[i] == '\'')
		{
			i++;
			while (word[i] && !ft_isquote(word[i], '\''))
				i++;
		}
		if (word[i] == '$')
			expand++;
	}
	return (expand);
}

static void	replace_variable(char **new_word, char *var_value, int *j)
{
	int	i;

	i = -1;
	if (ft_strcmp(var_value, "Value not found"))
	{
		while (var_value[++i])
			(*new_word)[(*j)++] = var_value[i];
	}
}

void	handle_expand(t_expansion *exp, int *ije)
{
	if (ft_strcmp(exp->var_name[ije[2]], "$"))
		ije[0]++;
	ije[0] += ft_strlen(exp->var_name[ije[2]]);
	replace_variable(&(exp->new_word), exp->var_value[ije[2]++], &ije[1]);
}
