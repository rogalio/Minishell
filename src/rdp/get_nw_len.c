/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:25:13 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 11:29:23 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "builtins.h"

static int	check_if_expand(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '$')
			return (1);
	}
	return (0);
}

static int	check_if_quotes(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'')
			return (1);
		if (word[i] == '\"')
			return (1);
	}
	return (0);
}

int	get_nw_len(char *word, t_expansion *exp)
{
	int	expand;
	int	quotes;
	int	len;

	len = ft_strlen(word);
	expand = check_if_expand(word);
	quotes = check_if_quotes(word);
	if (!expand && quotes)
		return ((len - 2));
	else if (expand && !quotes)
		return (get_nw_len_expand(word, len, exp));
	else
		return ((get_nw_len_expand(word, len, exp) - 2));
}
