/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:23:28 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 10:44:37 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "builtins.h"

/*
char	*get_env_value(t_env *env, const char *var_name)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(env->name, var_name))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
*/

char	*get_env_value(t_env *env, const char *var_name)
{
	int	i;

	i = 0;
	while (env)
	{
		i = 0;
		while (env->name[i] && var_name[i] && env->name[i] == var_name[i])
			i++;
		if (!var_name[i] && !env->name[i])
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

int	len_plus_exp_size(int len, t_expansion *exp)
{
	int	i;

	i = -1;
	while (exp->var_name[++i])
	{
		exp->var_value[i] = get_env_value(exp->env, exp->var_name[i]);
		if (exp->var_value[i])
			len += ft_strlen(exp->var_value[i]);
	}
	return (len);
}

