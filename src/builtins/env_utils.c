/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:17:00 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 17:39:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

//dans set_shlvl si shlvl = 1 exporter FIRST_LAUNCH
//verifier si shlvl est la sinon l'exporter

void	change_shlvl_value(t_env *env, char *char_shlvl_nb)
{
	char	*tmp;

	tmp = NULL;
	while (env)
	{
		if (!ft_strncmp(env->name, "SHLVL", (ft_strlen("SHLVL") + 1)))
		{
			tmp = env->value;
			env->value = char_shlvl_nb;
			free(tmp);
			return ;
		}
		env = env->next;
	}
	return ;
}

int	set_shlvl(t_env *env, int shlvl_nb)
{
	char	*shlvl;
	char	*char_shlvl_nb;

	shlvl = NULL;
	char_shlvl_nb = ft_itoa(shlvl_nb);
	if (!char_shlvl_nb)
		return (0);
	if (shlvl_nb == 1)
	{
		if (!add_to_env_list(&env, "FIRST_LAUNCH=yes"))
			return (0);
	}
	shlvl = getenv("SHLVL");
	if (!shlvl)
	{
		if (!add_to_env_list(&env, "SHLVL="))
			return (0);
	}
	change_shlvl_value(env, char_shlvl_nb);
	return (1);
}

int	init_shlvl(t_env *env)
{
	int		shlvl_nb;
	char	*shlvl;
	char	*first_launch;

	shlvl_nb = 1;
	shlvl = NULL;
	first_launch = getenv("FIRST_LAUNCH");
	if (!first_launch)
	{
		if (!set_shlvl(env, shlvl_nb))
			return (0);
	}
	else
	{
		shlvl = getenv("SHLVL");
		if (shlvl)
			shlvl_nb = set_shlvl(env, (ft_atoi(shlvl) + 1));
		else
			shlvl_nb = set_shlvl(env, shlvl_nb);
		if (!shlvl_nb)
			return (0);
	}
	return (1);
}

int	init_basic_env(t_env **env)
{
	int		i;
	char	cwd[1024];
	char	*tmp;

	i = -1;
	tmp = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (!tmp)
		return (0);
	if (!add_to_env_list(env, tmp))
		return (free(tmp), 0);
	free(tmp);
	if (!add_to_env_list(env, "_=/usr/bin/env"))
		return (0);
	return (1);
}
