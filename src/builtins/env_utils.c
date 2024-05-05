/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:17:00 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/05 20:40:05 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

//dans set_shlvl si shlvl = 1 exporter FIRST_LAUNCH
//verifier si shlvl est la sinon l'exporter

int	set_shlvl(t_env *env, int shlvl_nb)
{
	char	*shlvl;
	char	*char_shlvl_nb;

	shlvl = NULL;
	char_shlvl_nb = ft_itoa(shlvl_nb);
	if  (!char_shlvl_nb)
		return (0);
	if (shlvl == 1)
	{
		if (!add_to_env_list(&env, "FIRST_LAUNCH=lauched"))
			return (0);
	}
	shlvl = getenv("SHLVL");
	if (!shlvl)
	{
		if (!add_to_env_list(&env, "SHLVL="))
			return (0);
	}
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
			shlvl_nb  = set_shlvl(env, (ft_atoi(shlvl) + 1));
		else
			shlvl_nb  = set_shlvl(env, shlvl_nb);
		if (!shlvl_nb)
			return (0);
	}
	return (1);
}
