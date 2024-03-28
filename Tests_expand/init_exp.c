/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:58:23 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 16:29:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

t_expansion	*init_exp(void)
{
	t_expansion	*exp;

	exp = calloc(1, sizeof(t_expansion));
	if (!exp)
		return (NULL);
	return (exp);
}

static int	fill_var_name(char *word, int nb_expand, t_expansion *exp)
{
	int	i;

	i = -1;
	while (nb_expand-- && *word)
	{
		while (*word && *word != '$')
			word++;
		exp->var_name[++i] = extract_var_name(word);
		if (!exp->var_name[i])
			return (0);
		len -= strlen(exp->var_name[i]);
	}
	return (1);
}

char	**create_var_name(t_expansion *exp)
{
	char	**var_name;

	var_name = calloc((exp->nb_expand + 1), sizeof(char *));
	if (!var_name)
		return (NULL);
	if (!fill_var_name())
		return (free(var_name), NULL);
	return (var_name);
}
