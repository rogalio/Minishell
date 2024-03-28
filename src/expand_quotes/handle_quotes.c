/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:38 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 11:25:28 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	handle_single_quote(char *word, char *new_word, int *i, int *j)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
		new_word[(*j)++] = word[(*i)++];
	(*i)++;
}


int	handle_double_quote(char *word, char *new_word, char *var_value, int *i, int *j)
{
	int	nb_expand;

	nb_expand = 0;
	(*i)++;
	while (word[*i] && word[*i] != '\"')
	{
		if (word[*i] == '$')
		{
			nb_expand++;
			handle_expand(&word, new_word, var_value, i, j);
		}
		else
			new_word[(*j)++] = word[(*i)++];
	}
	(*i)++;
	return (nb_expand);
}