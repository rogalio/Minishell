/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:58:23 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/19 18:52:16 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

t_expansion	*init_exp(void)
{
	t_expansion	*exp;

	exp = ft_calloc(1, sizeof(t_expansion));
	if (!exp)
		return (NULL);
	return (exp);
}

static int	fill_var_name(char *word, char **var_name, int nb_expand)
{
	int	i;

	i = -1;
	while (nb_expand-- && *word)
	{
		while (*word && *word != '$')
			word++;
		if (!is_valid_variable_char(*(word + 1)))
		{
			var_name[++i] = ft_strdup("$");
			word++;
		}
		else
			var_name[++i] = extract_var_name(++word);
		if (!var_name[i])
			return (0);
	}
	return (1);
}

char	**create_var_name(char *word, t_expansion *exp)
{
	char	**var_name;

	var_name = ft_calloc((exp->nb_expand + 1), sizeof(char *));
	if (!var_name)
		return (NULL);
	if (!fill_var_name(word, var_name, exp->nb_expand))
		return (free_exp_tab(var_name), free(var_name), NULL);
	return (var_name);
}

static int	fill_var_value(char **var_value, char **var_name, t_env *env)
{
	int	i;

	i = -1;
	while (var_name[++i])
	{
		if (!ft_strcmp(var_name[i], "$"))
			var_value[i] = ft_strdup("$");
		else
			var_value[i] = get_env_value(env, var_name[i]);
		if (!var_value[i])
			return (0);
	}
	return (1);
}

char	**create_var_value(t_expansion *exp)
{
	char	**var_value;

	var_value = ft_calloc((exp->nb_expand + 1), sizeof(char *));
	if (!var_value)
		return (NULL);
	if (!fill_var_value(var_value, exp->var_name, exp->env))
		return (free_exp_tab(var_value), free(var_value), NULL);
	return (var_value);
}
