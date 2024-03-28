/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:38 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 13:57:58 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	handle_single_quote(char *word, char *new_word, int *ij)
{
	ij[0]++;
	while (word[ij[0]] && word[ij[0]] != '\'')
		new_word[ij[1]++] = word[ij[0]++];
	ij[0]++;
}


int	handle_double_quote(char *word, char *new_word, char *var_value, int *ij)
{
	int	nb_expand;

	nb_expand = 0;
	ij[0]++;
	while (word[ij[0]] && word[ij[0]] != '\"')
	{
		if (word[ij[0]] == '$')
		{
			nb_expand++;
			handle_expand(&word, new_word, var_value, ij);
		}
		else
			new_word[ij[1]++] = word[ij[0]++];
	}
	ij[0]++;
	return (nb_expand);
}
