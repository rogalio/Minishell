/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/14 14:58:09 by cabdli           ###   ########.fr       */
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

/*
char	*get_env_value(t_env *env, const char *var_name)
{
	int	j;
	int	var_len;

	j = 0;
	var_len = ft_strlen(var_name);
	while (env)
	{
		j = 0;
		while (env[i][j] && env[i][j] == var_name[j] && j < var_len)
			j++;
		if (j == var_len && env[i][j] == '=')
			return (ft_strdup(&env[i][j + 1]));
		env = env->next;
	}
	return (ft_strdup(""));
}
*/

int	is_valid_variable_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*extract_variable_name(char *word, int *i)
{
	int		j;
	char	*var_name;

	j = 0;
	while (word[*i] && is_valid_variable_char(word[*i]))
	{
		(*i)++;
		j++;
	}
	var_name = malloc((j + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	*i -= j;
	j = 0;
	while (word[*i] && is_valid_variable_char(word[*i]))
		var_name[j++] = word[(*i)++];
	var_name[j] = '\0';
	return (var_name);
}

void	replace_variable(char **new_word, t_env *env, const char *var_name, int *j)
{
	char	*var_value;

	var_value = get_env_value(env, var_name);
	while (var_value && *var_value)
		(*new_word)[(*j)++] = *var_value++;
}

void	handle_single_quote(char *word, char *new_word, int *i, int *j)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
		new_word[(*j)++] = word[(*i)++];
	(*i)++;
}

void	handle_variable(char **word, char *new_word, t_env *env, int *i, int *j)
{
	char	*var_name;

	(*i)++;
	if ((*word)[*i] == '?')
	{
		(*i)++;
		new_word[(*j)++] = '0';
		return ;
	}
	var_name = extract_variable_name(*word, i);
	replace_variable(&new_word, env, var_name, j);
	free(var_name);
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

t_expansion	*init_expansion(char *word)
{
	t_expansion	*exp;

	exp = malloc(sizeof(t_expansion));
	if (!exp)
		return (NULL);
	exp->new_word_capacity = ft_strlen(word) * 2;
	exp->new_word = malloc(exp->new_word_capacity * sizeof(char));
	if (!exp->new_word)
	{
		free(exp);
		return (NULL);
	}
	exp->new_word_len = 0;
	return (exp);
}

void	expand_variables_and_handle_quotes(char **word, t_env *env)
{
	int			i;
	int			j;
	t_expansion	*exp;

	exp = init_expansion(*word);
	if (!exp)
		return ;
	i = 0;
	j = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'')
			handle_single_quote(*word, exp->new_word, &i, &j);
		else if ((*word)[i] == '\"')
			handle_double_quote(*word, exp->new_word, env, &i, &j);
		else if ((*word)[i] == '$')
			handle_variable(word, exp->new_word, env, &i, &j);
		else
			exp->new_word[j++] = (*word)[i++];
	}
	exp->new_word[j] = '\0';
	free(*word);
	*word = exp->new_word;
	free(exp);
}

