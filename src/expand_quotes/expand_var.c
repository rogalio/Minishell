/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/27 11:49:04 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "token.h"
#include "parser.h"
#include "builtins.h"

void	free_expansion(t_expansion *exp)
{
	if (exp)
	{
		free(exp->new_word);
		free(exp);
	}
}

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

t_expansion	*init_expansion(char *word, t_env *env)
{
	t_expansion	*exp;

	exp = ft_calloc(1, sizeof(t_expansion));
	if (!exp)
		return (NULL);
	exp->env = env;
	exp->quotes = check_if_quotes(word);
	exp->expand = check_if_expand(word);
	exp->nw_len = get_nw_len(word, exp);
	exp->new_word = ft_calloc((exp->nw_len + 1), sizeof(char));
	if (!exp->new_word)
		return (free_expansion(exp), NULL);
	return (exp);
}

void	handle_expand_quotes(char **word, t_env *env)
{
	int			i;
	int			j;
	t_expansion	*exp;
	char		**tmp_var_val;

	i = 0;
	j = 0;
	tmp_var_val = NULL;
	exp = init_expansion(*word, env);
	if (!exp)
		return ;
	tmp_var_val = exp->var_value;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'')
			handle_single_quote(*word, exp->new_word, &i, &j);
		else if ((*word)[i] == '\"')
			tmp_var_val += handle_double_quote(*word, exp->new_word, *tmp_var_val, &i, &j);
		else if ((*word)[i] == '$')
		{
			handle_expand(word, exp->new_word, (*tmp_var_val), &i, &j);
			tmp_var_val++;
		}
		else
			exp->new_word[j++] = (*word)[i++];
	}
	free(*word);
	*word = exp->new_word;
	free_expansion(exp);
}

