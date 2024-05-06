/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:57:33 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 19:03:02 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "signals.h"
#include "token.h"
#include "data.h"
#include "exp_quotes.h"

// Splits the input on the first '=' encountered that isn't within quotes
int	parse_export_arg(char *arg, char **name, char **value)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (arg[i])
	{
		if (arg[i] == '"' && in_quote == 0)
			in_quote = 1;
		else if (arg[i] == '"' && in_quote == 1)
			in_quote = 0;
		else if (arg[i] == '=' && !in_quote)
			break ;
		i++;
	}
	*name = ft_strndup(arg, i);
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
	else
		*value = NULL;
	if (!*name)
		return (-1);
	return (0);
}

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*create_env_var(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	update_env_var(t_env *env, char *value)
{
	free(env->value);
	env->value = value;
}

void	add_env_var(t_data *data, t_env *new, t_env *last)
{
	if (!data->env)
		data->env = new;
	else
		last->next = new;
}
