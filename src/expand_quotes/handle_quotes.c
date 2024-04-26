/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:38 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/26 12:38:11 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

int	count_quotes(char *word)
{
	int		nb_quotes;
	int		i;
	char	quote;

	nb_quotes = 0;
	i = -1;
	quote = '\0';
	while (word[++i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			quote = word[i++];
			while (word[i] && !ft_isquote(word[i], quote))
				i++;
			nb_quotes += 2;
		}
	}
	return (nb_quotes);
}

void	handle_single_quote(char *word, char *new_word, int *ije)
{
	ije[0]++;
	while (word[ije[0]] && word[ije[0]] != '\'')
		new_word[ije[1]++] = word[ije[0]++];
	ije[0]++;
}

void	handle_double_quote(char *word, t_expansion *exp, int *ije)
{
	ije[0]++;
	while (word[ije[0]] && word[ije[0]] != '\"')
	{
		if (word[ije[0]] == '$')
			handle_expand(exp, ije);
		else
			exp->new_word[ije[1]++] = word[ije[0]++];
	}
	ije[0]++;
}

void	handle_quotes(char *word, t_expansion *exp, int *ije)
{
	if (word[ije[0]] == '\'')
		handle_single_quote(word, exp->new_word, ije);
	else
		handle_double_quote(word, exp, ije);
}
