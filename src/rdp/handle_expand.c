/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:09:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/26 15:43:23 by cabdli           ###   ########.fr       */
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
	return (ft_isalnum || c == '_');
}

static char	*extract_variable_name(char *word, int *i)
{
	int		j;
	char	*var_name;

	j = 0;
	var_name = NULL;
	while (word[*i] && is_valid_variable_char(word[*i]))
	{
		(*i)++;
		j++;
	}
	var_name = ft_calloc((j + 1), sizeof(char));
	if (!var_name)
		return (NULL);
	*i -= j;
	j = 0;
	while (word[*i] && is_valid_variable_char(word[*i]))
		var_name[j++] = word[(*i)++];
	// var_name[j] = '\0';
	return (var_name);
}

static void	replace_variable(char **new_word, t_env *env, const char *var_name, int *j)
{
	char	*var_value;

	var_value = get_env_value(env, var_name);
	while (var_value && *var_value)
		(*new_word)[(*j)++] = *var_value++;
}

void	handle_expand(char **word, char *new_word, t_env *env, int *i, int *j)
{
	char	*var_name;

	var_name = NULL;
	(*i)++;
	if ((*word)[*i] == '?')
	{
		(*i)++;
		new_word[(*j)++] = '0';
		return ;
	}
	var_name = extract_variable_name(*word, i);
	printf("var_name = %s\n\n", var_name);
	replace_variable(&new_word, env, var_name, j);
	printf("var_name = %s\n\n", var_name);
	// free(var_name);
}
