/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/25 17:21:41 by cabdli           ###   ########.fr       */
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

void	ensure_capacity(t_expansion *exp, int additional_size)
{
	if (exp->new_word_len + additional_size >= exp->new_word_capacity)
	{
		exp->new_word_capacity *= 2;
		exp->new_word = realloc(exp->new_word, \
		exp->new_word_capacity * sizeof(char));
		// Vérifiez si realloc a réussi
	}
}

char	*get_env_value(t_env *env, const char *var_name)
{
	int	i;

	i = 0;
	while (env)
	{
		i = 0;
		while (env->name[i] && var_name[i] && env->name[i] == var_name[i])
			i++;
		if (!var_name[i] && !env->name[i])
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

t_expansion	*init_expansion(char *word)
{
	t_expansion	*exp;

	exp = ft_calloc(1, sizeof(t_expansion));
	if (!exp)
		return (NULL);
	// exp->new_word_size = ft_strlen(word) * 2;
	// get_new_word_size()
	exp->new_word = ft_calloc(exp->new_word_size, sizeof(char));
	if (!exp->new_word)
	{
		free(exp);
		return (NULL);
	}
	exp->new_word_len = 0;
	return (exp);
}

void	expand_var_handle_quotes(char **word, t_env *env)
{
	int			i;
	int			j;
	t_expansion	*exp;

	i = 0;
	j = 0;
	exp = init_expansion(*word);
	if (!exp)
		return ;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'')
			handle_single_quote(*word, exp->new_word, &i, &j);
		else if ((*word)[i] == '\"')
			handle_double_quote(*word, exp->new_word, env, &i, &j);
		else if ((*word)[i] == '$')
			handle_expand(word, exp->new_word, env, &i, &j);
		else
			exp->new_word[j++] = (*word)[i++];
	}
	exp->new_word[j] = '\0';
	free(*word);
	*word = exp->new_word;
	free(exp);
}

