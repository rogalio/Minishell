/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 12:49:10 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

int	get_nb_expand(char *word)
{
	int	i;
	int	expand;
	int	dble_quote;

	i = -1;
	expand = 0;
	dble_quote = 0;
	while (word[++i])
	{
		if (word[i] == '\'' && !dble_quote)
		{
			while (word[++i] && !ft_isquote(word[i], '\''))
				;
		}
		if (word[i] == '\"')
		{
			if (!dble_quote)
				dble_quote = 1;
			else
				dble_quote = 0;
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
