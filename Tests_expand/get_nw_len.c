/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:25:13 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 13:53:03 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
// #include "builtins.h"

static int	len_minus_var_name(int len, int nb_expand, char **var_name)
{
	int	i;

	i = 0;
	while (nb_expand--)
		len -= (ft_strlen(var_name[i++]) + 1);
	return (len);
}

int	len_plus_value_size(int len, int nb_expand, char **var_value)
{
	int	i;

	i = 0;
	while (nb_expand--)
	{
		if (ft_strcmp(var_value[i], "Value not found"))
			len += ft_strlen(var_value[i++]);
		else
			i++;
	}
	return (len);
}

/*
static int	len_plus_value_size(int len, int nb_expand, char **var_value)
{
	int	i;

	i = 0;
	while (nb_expand)
	{
		if (!strcmp(var_value[i], "Value not found"))
		{
			i++;
			nb_expand--;
		}
		else
		{
			len += strlen(var_value[i++]);
			nb_expand--;
		}
	}
	return (len);
}
*/

static int	get_nw_len_expand(int len, t_expansion *exp)
{
	len = len_minus_var_name(len, exp->nb_expand, exp->var_name);
	len = len_plus_value_size(len, exp->nb_expand, exp->var_value);
	return (len);
}

int	get_nw_len(char *word, t_expansion *exp)
{
	int	len;

	len = ft_strlen(word);
	if (!exp->nb_expand && exp->quotes)
		return ((len - 2));
	else if (exp->nb_expand && !exp->quotes)
		return (get_nw_len_expand(len, exp));
	else
		return (((get_nw_len_expand(len, exp)) - 2));
}
