/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:50:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 16:33:14 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	env(t_data *data, t_minishell *minishell)
{
	t_env	*env;

	(void)minishell;
	env = data->env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		else
		{
			if (!env->check_equal)
				printf("%s\n", env->name);
		}
		env = env->next;
	}
	return (0);
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

t_env	*create_env_node(char *env_entry)
{
	t_env	*node;
	char	*separator;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	separator = ft_strchr(env_entry, '=');
	if (separator)
	{
		node->name = ft_strndup(env_entry, separator - env_entry);
		if (!node->name)
			return (free(node), NULL);
		node->value = ft_strdup(separator + 1);
		if (!node->value)
			return (free(node->name), free(node), NULL);
	}
	else
	{
		node->name = ft_strdup(env_entry);
		if (!node->name)
			return (free(node), NULL);
	}
	return (node);
}

int	add_to_env_list(t_env **head, char *envp)
{
	static t_env	*temp;
	t_env			*node;

	node = create_env_node(envp);
	if (!node)
		return (free_env(head), 0);
	if (!*head)
	{
		*head = node;
		temp = *head;
	}
	else
	{
		temp->next = node;
		temp = temp->next;
	}
	return (1);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env_list;

	i = -1;
	env_list = NULL;
	while (envp[++i])
	{
		if (!add_to_env_list(&env_list, envp[i]))
			return (NULL);
	}
	return (env_list);
}
