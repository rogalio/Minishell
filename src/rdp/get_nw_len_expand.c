/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:14:21 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/26 17:32:07 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "builtins.h"

static int	get_nb_expand(char *word)
{
	int	i;
	int	expand;

	i = -1;
	expand = 0;
	while (word[++i])
	{
		if (word[i] == '$')
			expand++;
	}
	return (expand);
}

static int	len_minus_var_name(int len, char *word, int nb_expand)
{
	while (nb_expand && *word)
	{
		while (*word && *word != '$')
			*word++;
		len--;
		while (*word && is_valid_variable_char(*word))
			
	}
}

int	get_nw_len_expand(char *word, int len, t_env *env)
{
	char	*tmp;
	int		nb_expand;

	tmp = word;
	nb_expand = get_nb_expand(word);
	
	len = len_minus_var_name(len, word, nb_expand);
	
}
