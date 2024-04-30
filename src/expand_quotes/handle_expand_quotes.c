/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/30 17:26:01 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

static int	exp_expand(t_expansion	**exp, char *word)
{
	(*exp)->nb_expand = get_nb_expand(word);
	if ((*exp)->nb_expand == 0)
		return (1);
	(*exp)->var_name = create_var_name(word, *exp);
	if (!(*exp)->var_name)
		return (free_expansion(*exp), 0);
	(*exp)->var_value = create_var_value(*exp);
	if (!(*exp)->var_value)
		return (free_expansion(*exp), 0);
	return (1);
}

static t_expansion	*create_expansion(char *word, t_env *env)
{
	t_expansion	*exp;

	exp = init_exp();
	if (!exp)
		return (NULL);
	exp->env = env;
	exp->quotes = count_quotes(word);
	if (!exp_expand(&exp, word))
		return (NULL);
	exp->nw_len = get_nw_len(word, exp);
	exp->new_word = ft_calloc((exp->nw_len + 1), sizeof(char));
	if (!exp->new_word)
		return (free_expansion(exp), NULL);
	return (exp);
}

int	handle_expand_quotes(char **word, t_env *env)
{
	int			ije[3];
	t_expansion	*exp;

	bzero(ije, sizeof(ije));
	exp = NULL;
	if (!expand_quotes(*word))
		return (1);
	exp = create_expansion(*word, env);
	if (!exp)
		return (0);
	while ((*word)[ije[0]])
	{
		if ((*word)[ije[0]] == '\'' || (*word)[ije[0]] == '\"')
			handle_quotes(*word, exp, ije);
		else if ((*word)[ije[0]] == '$')
			handle_expand(exp, ije);
		else
			exp->new_word[ije[1]++] = (*word)[ije[0]++];
	}
	free(*word);
	*word = exp->new_word;
	return (free_expansion(exp), 1);
}
