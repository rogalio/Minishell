/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:24:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/02 13:39:29 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	get_path(t_data *data, char **path)
{
	if (!data->args[1])
	{
		*path = get_env_var(data->env, "HOME");
		if (!*path)
			*path = ".";
	}
	else if (data->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (0);
	}
	else if (ft_strcmp(data->args[1], "-") == 0)
	{
		*path = get_env_var(data->env, "OLDPWD");
		if (!*path)
			*path = ".";
		ft_putstr_fd(*path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		*path = data->args[1];
	return (1);
}

void	set_env_var(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = malloc(sizeof(t_env));
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	env->next = NULL;
}

int	cd(t_data *data, t_minishell *minishell)
{
	char	*path;
	char	*cwd;

	(void)minishell;
	if (!get_path(data, &path))
		return (UNEXPEC_ERR);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (UNEXPEC_ERR);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd: invalid path\n", STDERR_FILENO);
		return (UNEXPEC_ERR);
	}
	set_env_var(data->env, "OLDPWD", get_env_var(data->env, "PWD"));
	set_env_var(data->env, "PWD", cwd);
	free(cwd);
	return (SUCCESS);
}
