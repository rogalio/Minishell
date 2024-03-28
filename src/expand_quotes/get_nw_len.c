/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nw_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:25:13 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 11:50:20 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "builtins.h"

int	get_nw_len(char *word, t_expansion *exp)
{
	int	len;

	len = ft_strlen(word);
	if (!exp->expand && exp->quotes)
		return ((len - 2));
	else if (exp->expand && !exp->quotes)
		return (get_nw_len_expand(word, len, exp));
	else
		return ((get_nw_len_expand(word, len, exp) - 2));
}
