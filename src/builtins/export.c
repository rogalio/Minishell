/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:08:16 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 16:23:38 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:58:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/12 19:50:48 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "signals.h"
#include "token.h"
#include "data.h"
#include "exp_quotes.h"

bool	check_equal(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (true);
	}
	return (false);
}

// Splits the input on the first '=' encountered that isn't within quotes
static int	parse_export_arg(char *arg, char **name, char **value)
{
	int i = 0;
	int in_quote = 0;

	printf("arg = %s\n", arg);
	while (arg[i] && (arg[i] != '=' || in_quote))
	{
		if (arg[i] == '"' && in_quote == 0)
			in_quote = 1;
		else if (arg[i] == '"' && in_quote == 1)
			in_quote = 0;
		i++;
	}
	if (arg[i] != '=' || i == 0) // No '=' or malformed input
		return (-1);
	*name = ft_strndup(arg, i);
	*value = ft_strdup(arg + i + 1);
	if (!*name || !*value)
		return (-1);
	return (0);
}

// Add or update an environment variable
static void	update_or_add_env(t_data *data, char *name, char *value)
{
	t_env	*env = data->env;
	t_env	*new;
	t_env	*prev = NULL;

	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
			free(env->name);
			env->name = name;
			env->value = value;
			return ;
		}
		prev = env;
		env = env->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!data->env)
		data->env = new;
	else
		prev->next = new;
}

//print export
void print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env->name, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

static int validate_and_split_arg(char *arg, char **name, char **value)
{
	if (parse_export_arg(arg, name, value) == -1)
		return (-1);

	if (!is_valid_variable_char((*name)[0]))
	{
		free(*name);
		free(*value);
		*name = NULL;
		*value = NULL;
		return (-1);
	}
	return (0);
}


static int process_export_argument(t_data *data, char *arg)
{
	char *name = NULL;
	char *value = NULL;

	if (validate_and_split_arg(arg, &name, &value) == -1)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (-1);
	}

	update_or_add_env(data, name, value);
	return (0);
}


// Main export function
int	export(t_data *data, t_minishell *minishell)
{
	char	**args;
	int		i;

	args = minishell->pipeline->commands[0]->args;
	i = 1;
	if (!args[i])
	{
		print_export(data->env);
		return (0);
	}
	while (args[i])
	{
		if (process_export_argument(data, args[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}
