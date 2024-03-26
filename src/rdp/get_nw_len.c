/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:25:13 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/26 17:32:26 by cabdli           ###   ########.fr       */
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

int	get_nw_len(char *word, t_env *env, t_expansion *exp)
{
	int	i;
	int	expand;
	int	quotes;
	int	len;

	i = -1;
	len = ft_strlen(word);
	expand = check_if_expand(word);
	quotes = check_if_quotes(word);
	if (!expand && quotes)
		return ((len - 2));
	else if (expand && !quotes)
		return (get_nw_len_expand(word, len, env, exp));
	else
		return ((get_nw_len_expand(word, len, env) - 2));
}

/*
	while (word[++i])
	{
		if (word[i] == '\'')
			handle_single_quote(*word, exp->new_word, &i, &j);
		else if (word[i] == '\"')
			handle_double_quote(*word, exp->new_word, env, &i, &j);
		else if (word[i] == '$')
			handle_expand(word, exp->new_word, env, &i, &j);
		else
			exp->new_word[j++] = word[i++];
*/

