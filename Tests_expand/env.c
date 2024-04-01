/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:50:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/01 15:31:00 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		else
			printf("%s\n", env->name);
		env = env->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_env	*create_env_node(char *env_entry)
{
	t_env	*node;
	char	*separator;

	node = calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	separator = strchr(env_entry, '=');
	if (separator)
	{
		node->name = strndup(env_entry, separator - env_entry);
		node->value = strdup(separator + 1);
	}
	else
	{
		node->name = strdup(env_entry);
		node->value = NULL;
	}
	return (node);
}

t_env	*add_to_env_list(t_env *head, t_env *new_node)
{
	t_env	*temp;

	if (!head)
		return (new_node);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (head);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = add_to_env_list(env, create_env_node(envp[i]));
		i++;
	}
	return (env);
}
