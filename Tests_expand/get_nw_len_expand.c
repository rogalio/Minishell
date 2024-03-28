/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:14:21 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 15:49:44 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "builtins.h"

/*
 Selon la norme POSIX, les noms de variables d'environnement
 peuvent contenir des lettres majuscules et minuscules,
 des chiffres et le caractère souligné '_'.
*/
static int	is_valid_variable_char(char c)
{
	return (isalnum(c) || c == '_');
}

static char	*extract_var_name(char *word)
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
	*word -= var_len;
	while (*word && is_valid_variable_char(*word))
		var_name[i++] = *word++;
	return (var_name);
}

static int	len_minus_var_name(int len, char *word, int nb_expand, \
t_expansion *exp)
{
	int	i;

	i = -1;
	while (nb_expand-- && *word)
	{
		while (*word && *word != '$')
			word++;
		len--;
		exp->var_name[++i] = extract_var_name(word);
		if (!exp->var_name[i])
			return (0);
		len -= strlen(exp->var_name[i]);
	}
	return (len);
}

int	get_nw_len_expand(char *word, int len, t_expansion *exp)
{
	len = len_minus_var_name(len, word, exp->nb_expand, exp);
	len = len_plus_exp_size(len, exp);
	return (len);
}
