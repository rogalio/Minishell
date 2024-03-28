/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:44:22 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/28 17:21:10 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

/*
 Selon la norme POSIX, les noms de variables d'environnement
 peuvent contenir des lettres majuscules et minuscules,
 des chiffres et le caractère souligné '_'.
*/
int	is_valid_variable_char(char c)
{
	return (isalnum(c) || c == '_');
}

char	*extract_var_name(char *word)
{
	int		i;
	int		var_len;
	char	*var_name;

	i = 0;
	var_len = 0;
	var_name = NULL;
	while (*word && is_valid_variable_char(*word++))
		var_len++;
	var_name = calloc((var_len + 1), sizeof(char));
	if (!var_name)
		return (NULL);
	word -= (var_len +1);
	while (*word && is_valid_variable_char(*word))
		var_name[i++] = *word++;
	return (var_name);
}

char	*get_env_value(t_env *env, const char *var_name)
{
	while (env)
	{
		if (!strcmp(env->name, var_name))
			return (strdup(env->value));
		env = env->next;
	}
	return (strdup("Value not found"));
}

// char	*get_env_value(t_env *env, const char *var_name)
// {
// 	int	i;

// 	i = 0;
// 	while (env)
// 	{
// 		i = 0;
// 		while (env->name[i] && var_name[i] && env->name[i] == var_name[i])
// 			i++;
// 		if (!var_name[i] && !env->name[i])
// 			return (strdup(env->value));
// 		env = env->next;
// 	}
// 	return (strdup("Value not found"));
// }
