/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/27 16:19:36 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

/*
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
*/

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

static int	get_nb_expand(char *word)
{
	int	i;
	int	expand;

	i = -1;
	expand = 0;
	while (word[++i])
	{
		if (word[i] == '$')
			expand++;
	}
	return (expand);
}

t_expansion	*create_expansion(char *word, t_env *env)
{
	t_expansion	*exp;

	exp = init_exp();
	if (!exp)
		return (NULL);
	exp->env = env;
	exp->quotes = check_if_quotes(word);
	exp->nb_expand = get_nb_expand(word);
	exp->var_name = create_var_name(exp);
	if (!exp->var_name)
		return (free_expansion(exp), NULL);
	
	exp->var_value = calloc((exp->nb_expand + 1), sizeof(char *));
	if (!exp->var_value)
		return (NULL);
	exp->nw_len = get_nw_len(word, exp);
	exp->new_word = calloc((exp->nw_len + 1), sizeof(char));
	if (!exp->new_word)
		return (free_expansion(exp), NULL);
	return (exp);
}

void	handle_expand_quotes(char **word, t_env *env)
{
	int			ij[2];
	t_expansion	*exp;
	char		**tmp_var_val;

	bzero(ij, sizeof(ij));
	tmp_var_val = NULL;
	exp = create_expansion(*word, env);
	if (!exp)
		return ;
	print_exp(exp);
	tmp_var_val = exp->var_value;
	while ((*word)[ij[0]])
	{
		if ((*word)[ij[0]] == '\'')
			handle_single_quote(*word, exp->new_word, ij);
		else if ((*word)[ij[0]] == '\"')
			tmp_var_val += handle_double_quote(*word, exp->new_word, *tmp_var_val, ij);
		else if ((*word)[ij[0]] == '$')
		{
			handle_expand(word, exp->new_word, (*tmp_var_val), ij);
			tmp_var_val++;
		}
		else
			exp->new_word[ij[1]++] = (*word)[ij[0]++];
	}
	free(*word);
	*word = exp->new_word;
	free_expansion(exp);
}

