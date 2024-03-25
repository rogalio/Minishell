/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:38 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/25 17:14:10 by cabdli           ###   ########.fr       */
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


void	handle_double_quote(char *word, char *new_word, t_env *env, int *i, int *j)
{
	(*i)++;
	while (word[*i] && word[*i] != '\"')
	{
		if (word[*i] == '$')
			handle_variable(&word, new_word, env, i, j);
		else
			new_word[(*j)++] = word[(*i)++];
	}
	(*i)++;
}