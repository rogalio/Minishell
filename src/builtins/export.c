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

//get_env
t_env	*get_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

//set_env
void	set_env(t_data *data, char *name, char *value)
{
	t_env	*env;

	env = get_env(data->env, name);
	if (env->value)
		free(env->value);
	env->value = value;
}

//add_env
void	add_env(t_data *data, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!data->env)
	{
		data->env = new;
		return ;
	}
	tmp = data->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		export_env(t_data *data, char *arg)
{
  char	*name;
	char	*value;
	char	*separator;

	separator = ft_strchr(arg, '=');
	if (!separator)
		return (0);
	name = ft_strndup(arg, separator - arg);
	if (!name)
		return (-1);
	value = ft_strdup(separator + 1);
	if (!value)
	{
		free(name);
		return (-1);
	}
	if (get_env(data->env, name))
		set_env(data, name, value);
	else
		add_env(data, name, value);
	return (0);
}

int		export_var(t_data *data, char *arg)
{
	char	*name;
	char	*value;

	name = ft_strdup(arg);
	if (!name)
		return (-1);
	value = ft_strdup("");
	if (!value)
	{
		free(name);
		return (-1);
	}
	if (get_env(data->env, name))
	{
		free(name);
		set_env(data, name, value);
	}
	else
		add_env(data, name, value);
	return (0);
}

int		export(t_data *data, t_minishell *minishell)
{
	int		i;
	int		ret;
	char	**args;

	i = 1;
	ret = 0;
	args = minishell->pipeline->commands[0]->args;
	if (!args[i])
	{
		print_env(data->env);
		return (0);
	}
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			ret = export_env(data, args[i]);
		else
			ret = export_var(data, args[i]);
		if (ret == -1)
			return (ret);
		i++;
	}
	return (ret);
}

// si export sans initialiser, le printenv ne laffiche pas

// tout ce qui est apres = doit etre mis entre double quote et si pas egal alors value = ""

// peut pas export le sign = ni les autre caracteres speciaux et doit afficher message derreur.