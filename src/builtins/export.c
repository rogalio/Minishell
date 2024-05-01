/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:08:16 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 17:39:30 by cabdli           ###   ########.fr       */
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

// Splits the input on the first '=' encountered that isn't within quotes
static int	parse_export_arg(char *arg, char **name, char **value)
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

// Add or update an environment variable
static void	update_or_add_env(t_data *data, char *name, char *value)
{
	t_env	*env;
	t_env	*new;
	t_env	*prev;

	env = data->env;
	new = NULL;
	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
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

void	print_export(t_env *env)
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

static int	validate_and_split_arg(char *arg, char **name, char **value)
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

static int	process_export_argument(t_data *data, char *arg)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
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

int	export(t_data *data, t_minishell *minishell)
{
	int		i;
	char	**args;

	i = 1;
	args = minishell->pipeline->commands[0]->args;
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

/*
bash-5.1$ export tata=
bash-5.1$ export | grep tata
export tata=""
bash-5.1$ env | grep tata
tata=
bash-5.1$ export wewe
bash-5.1$ export | grep wewe
export wewe
bash-5.1$ env | grep wewe
*/
