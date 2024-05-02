/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:19:56 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/02 13:41:33 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*search_in_current(const char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	**get_search_paths(t_env *env)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
	{
		free(path_env);
		return (NULL);
	}
	paths = ft_split2(path_env, ':');
	free(path_env);
	return (paths);
}

static char	*check_directories(char **dirs, const char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin_three(dirs[i], "/", cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(const char *cmd, t_minishell *minishell)
{
	char	**paths;
	char	*found_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || \
	ft_strncmp(cmd, "../", 3) == 0)
		return (search_in_current(cmd));
	paths = get_search_paths(minishell->data->env);
	if (!paths)
		return (free(paths), NULL);
	found_path = check_directories(paths, cmd);
	free_tab(paths);
	return (found_path);
}
